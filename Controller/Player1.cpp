#include "Player1.h"

using namespace controllers;

Player1::Player1(std::list<Explosion>& Explosions, std::list<Bullet>& Bullets, GameSprite& cSprite, Map& cMap, bool bIsPlayer, int objID, Move cMove)
    : Tank(Explosions, Bullets, cSprite, cMap, bIsPlayer, objID, cMove) {

    speed = PlayerSpeed;
    sSprite = cSprite.yellowTankSprite;
    initialPlace();
}

Player1::~Player1() {}

void Player1::checkMove() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        cLastMove = cMove = Move::UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        cLastMove = cMove = Move::DOWN;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        cLastMove = cMove = Move::LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        cLastMove = cMove = Move::RIGHT;
    }
    else {
        if (cMove != Move::NONE)
            cLastMove = cMove;
        cMove = Move::NONE;
    }
}

void Player1::initialPlace() {
    cMove = Move::UP;

    vecPosition.x = float(cMap.sScreen.nSides + cMap.sScreen.nBlockSize * 10);
    vecPosition.y = float(cMap.sScreen.topBot + cMap.sScreen.nBlockSize * 26);

    sSprite.setPosition(vecPosition);
    sSprite.setScale(cMap.sScreen.nScale, cMap.sScreen.nScale);

    this->updateImage();
}