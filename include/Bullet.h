#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
class Map;

class Bullet {
private:
    float mX, mY, mDx, mDy;
    int mDir;

    sf::Texture mTexture;

public:
    bool present; //is it shot?
    float timeBeforeShot;
	sf::Sprite mSprite;

    explicit Bullet(const float &x, const float &y);

	void shoot() { present = true; }
    void move(const sf::Int64 &time);
    void update(Map &map, const sf::Int64 &time, float &x, const float &y, const int &dir);
    void map_interaction(Map &map);
};
