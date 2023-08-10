#pragma once
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Bullet.h"
#include <utility>
class Map;

class Tank : private sf::NonCopyable  {
protected:
    float mX, mY, mWidth, mHeight, mDx, mDy, mSpeed;
    int mDir;
    float mCurrentFrame;
    bool mCollision;

    sf::String mFile;
    sf::Texture mTexture;

public:
    explicit Tank(const float &x, const float &y, const float &width, const float &height, const sf::String &file);

    bool life;

	Bullet bullet;
    sf::Sprite mSprite;

    void animate(const sf::Int64 &time);

    void collapse();
    virtual void move(const sf::Int64 &time) {}
    void map_interaction(Map &map);
    void tank_interaction();
};
