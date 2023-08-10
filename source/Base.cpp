#include "../include/Base.h"

Base::Base()
    : life(true) {
    mTexture.loadFromFile("media/baseSprite.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    mSprite.setPosition(336, 600);
}

void Base::setPosition(float fX, float fY) {
    mSprite.setPosition(fX, fY);
}