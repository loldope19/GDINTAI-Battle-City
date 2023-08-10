#pragma once
#include <SFML/Graphics.hpp>

class Powers {
private:
    sf::Texture mTexture;

public:
    enum PowerType {
        SPEED_UP, SPEED_DOWN, INVINCI_BASE, MINES, CHAOS
    } pType;

    bool life;
    sf::Sprite mSprite;

    Powers(float fX, float fY, int nPowerType);
    Powers(const Powers&);

};