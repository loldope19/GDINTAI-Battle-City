#include "../include/Base.h"

Base::Base(const Base&) {}

Base::Base(float fX, float fY, BaseType EType)
    : life(true) {
    if (EType == BaseType::PLAYER)
        mTexture.loadFromFile("media/baseSprite.png");
    else
        mTexture.loadFromFile("media/enemyBaseSprite.png");
    
    bType = EType;
    
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    mSprite.setPosition(fX, fY);
}

void Base::setPosition(float fX, float fY) {
    mSprite.setPosition(fX, fY);
}