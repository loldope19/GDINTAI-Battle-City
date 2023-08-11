#include "../include/Enemy.h"

Enemy::Enemy(const float &x, const float &y)
    : Tank(x, y, 39, 39, "media/enemySprites.png", 1), timeBeforeMoving(0.f), timeBeforeShot(0.f), 
      nHealth(3), nKills(0), currentState(AIState::SearchGoal) { }

// Movement function of the Enemy
void Enemy::move(const sf::Int64 &time) {
    mSpeed = 0.12f;
    timeBeforeMoving += time;

    if (timeBeforeMoving > 1000 + rand() % 501) {
        mDir = std::rand() % 4;
        timeBeforeMoving = 0.f;
    }

    switch (mDir) {
        case 0:     // Right
            mDx = mSpeed;
            mDy = 0;
            break;

        case 1:     // Left
            mDx = -mSpeed;
            mDy = 0;
            break;

        case 2:     // Down..?
            mDx = 0;
            mDy = mSpeed;
            break;

        case 3:     // Up..?
            mDx = 0;
            mDy = -mSpeed;
            break;
    }
    if (mCollision) tank_interaction();
    mX += mDx * time;
    mY += mDy * time;
}

void Enemy::moveAlongPath(const std::vector<sf::Vector2i> &path) {
    if (path.empty()) {
        // No path to follow
        return;
    }

    // Get the direction from the current position to the first tile in the path
    sf::Vector2i nextTile = path[0];
    sf::Vector2i direction = nextTile - sf::Vector2i(mX / 24, mY / 24);

    // Move the enemy in the determined direction
    if (direction.x == 1) {
        // Move right
        mDir = 0;
        mDx = mSpeed;
        mDy = 0;
    } else if (direction.x == -1) {
        // Move left
        mDir = 1;
        mDx = -mSpeed;
        mDy = 0;
    } else if (direction.y == 1) {
        // Move down
        mDir = 2;
        mDx = 0;
        mDy = mSpeed;
    } else if (direction.y == -1) {
        // Move up
        mDir = 3;
        mDx = 0;
        mDy = -mSpeed;
    }

}

// Sets enemy position
void Enemy::setPosition(float fX, float fY) {
    mX = fX;
    mY = fY;
}

// Gets enemy position
sf::Vector2i Enemy::getPosition() {
    return sf::Vector2i(mX, mY);
}

// Makes the enemy shoot
void Enemy::shoot(const float &time) {
    timeBeforeShot += time;

    if (timeBeforeShot > 1000.f) {
        if (!bullet.present)
            if (rand() % 2)
                bullet.present = true;

        timeBeforeShot = 0.f;
    }
}

// Handles the major updating algorithm of the enemy
void Enemy::update(const sf::Int64 &time, Map &map, const bool &collision, 
                   const sf::Vector2i &playerPos, const sf::Vector2i &basePlayer,
                   const sf::Vector2i &baseEnemy) {
    // Updating AI state based on conditions
    switch (currentState) {
        case AIState::ChasePlayer:
            if (calculateHeuristic(baseEnemy / 24, playerPos / 24) <= 6.0f)
                currentState = AIState::ProtectBase;
            else
                currentState = AIState::SearchGoal;
            break;
        
        case AIState::ProtectBase:
            if (calculateHeuristic(getPosition() / 24, playerPos / 24) <= 6.0f)
                currentState = AIState::ChasePlayer;
            else
                currentState = AIState::SearchGoal;
            break;
        
        case AIState::SearchGoal:
            if (calculateHeuristic(getPosition() / 24, playerPos / 24) <= 6.0f)
                currentState = AIState::ChasePlayer;
            if (calculateHeuristic(baseEnemy / 24, playerPos / 24) <= 6.0f)
                currentState = AIState::ProtectBase;
            break;
    }
    
    // Update the enemy's movement and shooting based on the current state
    std::vector<sf::Vector2i> path;
    switch (currentState) {
        case AIState::ChasePlayer:
            path = this->performAStarSearch(this->getPosition(), playerPos, map);
            moveAlongPath(path);
            break;
        
        case AIState::ProtectBase:
            path = this->performAStarSearch(this->getPosition(), baseEnemy, map);
            moveAlongPath(path);
            break;
        
        case AIState::SearchGoal:
            path = this->performAStarSearch(this->getPosition(), basePlayer, map);
            moveAlongPath(path);
            break;
    }
    
    // -------------------------------- //
    mCollision = collision;
    move(time);
    animate(time);

    mSpeed = 0.f;
    mSprite.setPosition(mX, mY);
    map_interaction(map);

    bullet.update(map, time, mX, mY, mDir);
    shoot(time);
}

// Runs when the Enemy steps on the Speed-Up Power Up
void Enemy::speedUp() {
    mSpeed = 0.24f;

    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        mSpeed = 0.12f;
        bEnemySpeedUp = false;
    }
}

// Runs when the Enemy steps on the Speed-Down Power Up
void Enemy::speedDown() {
    mSpeed = 0.06f;

    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        mSpeed = 0.12f;
        bEnemySpeedDown = false;
    }
}

// Runs when the Enemy steps on the Invincible Base Power Up, making their base invincible
void Enemy::invinciBase() {
    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        bEnemyInvBase = false;
    }
}

std::vector<sf::Vector2i> Enemy::performAStarSearch(const sf::Vector2i &start, const sf::Vector2i &goal, Map &map) {
    std::vector<sf::Vector2i> path;

    // Convert pixel positions to tile coordinates
    sf::Vector2i vecStart = start / 24;
    sf::Vector2i vecGoal = goal / 24;

    // Initialize open set (priority queue)
    std::priority_queue<Node> openSet;
    openSet.push({vecStart.x, vecStart.y, calculateHeuristic(vecStart, vecGoal), 0, 0});

    // Initialize closed set
    std::vector<std::vector<bool>> closedSet(30, std::vector<bool>(28, false));
    // Initialize cameFrom array
    std::vector<std::vector<sf::Vector2i>> cameFrom(30, std::vector<sf::Vector2i>(28, sf::Vector2i(-1, -1)));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.x == vecGoal.x && current.y == vecGoal.y) {
            // Goal reached, construct the path
            sf::Vector2i pathNode = vecGoal;
            while (pathNode != vecStart) {
                path.push_back(pathNode);
                pathNode = cameFrom[pathNode.x][pathNode.y];
            }
            path.push_back(vecStart);
            std::reverse(path.begin(), path.end());
            break;
        }

        closedSet[current.x][current.y] = true;

        // Define neighbor offsets
        std::vector<sf::Vector2i> neighborOffsets = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };

        for (const sf::Vector2i &offset : neighborOffsets) {
            sf::Vector2i neighborPos = sf::Vector2i(current.x + offset.x, current.y + offset.y);
            sf::Vector2i currentPos = sf::Vector2i(current.x, current.y);

            // Check if the neighbor is within bounds
            if (neighborPos.x >= 0 && neighborPos.x < 30 && neighborPos.y >= 0 && neighborPos.y < 28) {
                // Check if the neighbor is passable and not in the closed set
                if (map.get_tile(neighborPos.y, neighborPos.x) == ' ' && !closedSet[neighborPos.x][neighborPos.y]) {
                    // Calculate tentative g value (distance from start)
                    int tentativeG = current.g + 1;  // Assuming constant movement cost of 1

                    // Check if the neighbor is not in the open set or has a better g value
                    if (!openSetContains(openSet, neighborPos)) {
                        openSet.push({neighborPos.x, neighborPos.y, calculateHeuristic(neighborPos, vecGoal), tentativeG, 0});
                        cameFrom[neighborPos.x][neighborPos.y] = currentPos;
                    }
                }
            }
        }
    }

    return path;
}

bool Enemy::openSetContains(const std::priority_queue<Node> &openSet, const sf::Vector2i &pos) {
    std::priority_queue<Node> copy = openSet;
    while (!copy.empty()) {
        if (copy.top().x == pos.x && copy.top().y == pos.y) {
            return true;
        }
        copy.pop();
    }
    return false;
}

int Enemy::calculateHeuristic(const sf::Vector2i &start, const sf::Vector2i &goal) {
    // Calculate Manhattan distance as heuristic
    return std::abs(goal.x - start.x) + std::abs(goal.y - start.y);
}