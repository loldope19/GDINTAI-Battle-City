#include "../include/Enemy.h"

Enemy::Enemy(const float &x, const float &y)
    : Tank(x, y, 39, 39, "media/enemySprites.png"), timeBeforeMoving(0.f), timeBeforeShot(0.f) {

}

void Enemy::move(const sf::Int64 &time) {
    mSpeed = 0.1f;
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
