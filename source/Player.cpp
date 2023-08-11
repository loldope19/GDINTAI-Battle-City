#include "SFML/Window/Keyboard.hpp"
#include "../include/Player.h"
#include "../include/Map.h"

using sf::Keyboard;

Player::Player()
    : Tank(244, 600, 39, 39, "media/playerSprites.png", 0), nHealth(3), nKills(0) {
}

void Player::move(const sf::Int64 &time) {
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        mDir = 1;
        mSpeed = initialSpeed;
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        mDir = 0;
        mSpeed = initialSpeed;
    }

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        mDir = 3;
        mSpeed = initialSpeed;
    }

    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        mDir = 2;
        mSpeed = initialSpeed;
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

void Player::update(const sf::Int64 &time, Map &map, const bool &collision) {
    mCollision = collision;
    move(time);

    mSpeed = 0.f;
    mSprite.setPosition(mX, mY);
    animate(time);
    map_interaction(map);

    bullet.update(map, time, mX, mY, mDir);
    if (!bullet.present)
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            bullet.timeBeforeShot += time;
            if (bullet.timeBeforeShot > 10.f) {
                bullet.present = true;
                bullet.timeBeforeShot = 0.f;
            }
        }
}

void Player::setPosition(float fX, float fY) {
    mX = fX;
    mY = fY;
}

sf::Vector2i Player::getPosition() {
    return sf::Vector2i(mX, mY);
}

void Player::speedUp() {
    initialSpeed = 0.24f;

    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        initialSpeed = 0.12f;
        bPlayerSpeedUp = false;
    }
}

void Player::speedDown() {
    initialSpeed = 0.06f;

    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        initialSpeed = 0.12f;
        bPlayerSpeedDown = false;
    }
}

void Player::invinciBase() {
    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        bPlayerInvBase = false;
    }
}