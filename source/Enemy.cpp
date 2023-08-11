#include "../include/Enemy.h"

Enemy::Enemy(const float &x, const float &y)
    : Tank(x, y, 39, 39, "media/enemySprites.png", 1), timeBeforeMoving(0.f), timeBeforeShot(0.f), nHealth(3), nKills(0) {

}

void Enemy::move(const sf::Int64 &time) {
    mSpeed = 0.12f;
    timeBeforeMoving += time;

    if (timeBeforeMoving > 1000 + rand() % 501) {
        mDir = rand() % 4;
        timeBeforeMoving = 0.f;
    }

    switch (mDir) {
        case 0:
            mDx = mSpeed;
            mDy = 0;
            break;

        case 1:
            mDx = -mSpeed;
            mDy = 0;
            break;

        case 2:
            mDx = 0;
            mDy = mSpeed;
            break;

        case 3:
            mDx = 0;
            mDy = -mSpeed;
            break;
    }
    if (mCollision) tank_interaction();
    mX += mDx * time;
    mY += mDy * time;
}

void Enemy::setPosition(float fX, float fY) {
    mX = fX;
    mY = fY;
}

void Enemy::shoot(const float &time) {
    timeBeforeShot += time;

    if (timeBeforeShot > 1000.f) {
        if (!bullet.present)
            if (rand() % 2)
                bullet.present = true;

        timeBeforeShot = 0.f;
    }
}

void Enemy::update(const sf::Int64 &time, Map &map, const bool &collision) {
    mCollision = collision;
    move(time);

    mSpeed = 0.f;
    mSprite.setPosition(mX, mY);
    animate(time);
    map_interaction(map);

    bullet.update(map, time, mX, mY, mDir);
    shoot(time);
}

void Enemy::speedUp() {
    mSpeed = 0.24f;

    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        mSpeed = 0.12f;
        bEnemySpeedUp = false;
    }
}

void Enemy::speedDown() {
    mSpeed = 0.06f;

    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        mSpeed = 0.12f;
        bEnemySpeedDown = false;
    }
}

void Enemy::invinciBase() {
    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        bEnemyInvBase = false;
    }
}