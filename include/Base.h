#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Base : private sf::NonCopyable {
private:
    sf::Texture mTexture;

public:
    sf::Sprite mSprite;
    bool life;

    Base();

public:
    void setPosition(float fX, float fY);
};
