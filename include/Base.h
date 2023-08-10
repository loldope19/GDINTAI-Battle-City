#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Sprite.hpp>

class Base : private sf::NonCopyable {
private:
    sf::Texture mTexture;
    std::chrono::high_resolution_clock cClock;
    std::chrono::seconds duration = std::chrono::seconds(10);

public:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    enum BaseType {
        PLAYER, ENEMY
    } bType;

    sf::Sprite mSprite;
    bool life;
    bool bInvincible;

    Base(float fX, float fY, BaseType EType);
    Base(const Base&);

public:
    void setPosition(float fX, float fY);
    void invincible();
};
