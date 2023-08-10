#include "../include/Powers.h"

Powers::Powers(float fX, float fY, int nPowerType) : life(true) {
    switch (nPowerType) {
        case 0:
            mTexture.loadFromFile("media/speedUpSprite.png");
            pType = PowerType::SPEED_UP;
            break;
        case 1:
            mTexture.loadFromFile("media/speedDownSprite.png");
            pType = PowerType::SPEED_DOWN;
            break;
        case 2:
            mTexture.loadFromFile("media/invincibaseSprite.png");
            pType = PowerType::INVINCI_BASE;
            break;
        case 3:
            mTexture.loadFromFile("media/mineSprite.png");
            pType = PowerType::MINES;
            break;
        case 4:
            mTexture.loadFromFile("media/chaosSprite.png");
            pType = PowerType::CHAOS;
            break;
    }

    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    mSprite.setPosition(fX, fY);
}

Powers::Powers(const Powers&) {}