#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Sprite.hpp>

class Base : private sf::NonCopyable {
private:
    sf::Texture mTexture;

public:
    enum BaseType {
        PLAYER, ENEMY
    } bType;

    sf::Sprite mSprite;
    bool life;

    Base(float fX, float fY, BaseType EType);
    Base(const Base&);

public:
    void setPosition(float fX, float fY);
};
