#include "../include/Powers.h"

Powers::Powers(float fX, float fY, PowerType EType) : life(true) {
    switch (EType) {
        case PowerType::SPEED_UP:
            mTexture.loadFromFile("media/speedUpSprite.png");
            break;
        case PowerType::SPEED_DOWN:
            mTexture.loadFromFile("media/speedDownSprite.png");
            break;
        case PowerType::INVINCI_BASE:
            mTexture.loadFromFile("media/invincibaseSprite.png");
            break;
        case PowerType::MINES:
            mTexture.loadFromFile("media/mineSprite.png");
            break;
        case PowerType::CHAOS:
            mTexture.loadFromFile("media/chaosSprite.png");
            break;
    }

    pType = EType;

    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    mSprite.setPosition(fX, fY);
}

Powers::Powers(const Powers&) {}