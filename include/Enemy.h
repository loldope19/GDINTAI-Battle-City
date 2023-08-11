#pragma once
#include "Tank.h"
#include "Map.h"
#include <chrono>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

enum class TransitionType {
    PLAYER_NEARBY,
    PLAYER_NEAR_ENEMY_BASE,
    PLAYER_BASE_NEAR
};

enum class AIState {
    ChasePlayer,
    ProtectBase,
    SearchGoal
};

class Enemy : public Tank {
private:
    AIState currentState;
    sf::Vector2i goalPosition;

public:
    struct Node {
        int x, y;
        int f, g, h;
        Node* parent;

        bool bIsBrick;
        bool bIsSteel;
        bool bIsPlayer;
        bool bIsEnemy;

        bool operator<(const Node& other) const {
            return g + h > other.g + other.h;
        }
    };

    struct CompareNodes {       // Compares the f(n) for two nodes; essential for running the priority queue
        bool operator()(Node* node1, Node* node2) const {
            return node1->f > node2->f;
        }
    };

private:
    std::chrono::high_resolution_clock cClock;
    std::chrono::seconds duration = std::chrono::seconds(10);
    float timeBeforeMoving;
    float timeBeforeShot;

public:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    int nHealth, nKills;
    bool bEnemySpeedUp;
    bool bEnemySpeedDown;
    bool bEnemyInvBase;

public:
    Enemy(const float &x, const float &y);
    Enemy(const Enemy &copy) : Enemy(copy.mX, copy.mY){}

    void move(const sf::Int64 &time);
    void moveAlongPath(const std::vector<sf::Vector2i> &path);
    void shoot(const float &time);
    void update(const sf::Int64 &time, Map &map, const bool &collision, const sf::Vector2i &playerPos, const sf::Vector2i &basePos, const sf::Vector2i &baseEnemy);
    void speedUp();
    void speedDown();
    void invinciBase();
    void setPosition(float fX, float fY);
    sf::Vector2i getPosition();

    std::vector<sf::Vector2i> performAStarSearch(const sf::Vector2i &start, const sf::Vector2i &goal, Map &map);
    bool openSetContains(const std::priority_queue<Node> &openSet, const sf::Vector2i &pos);
    int calculateHeuristic(const sf::Vector2i &start, const sf::Vector2i &goal);
};
