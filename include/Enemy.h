#pragma once
#include "Tank.h"
#include <chrono>

class Enemy : public Tank {
private:
    std::chrono::high_resolution_clock cClock;
    std::chrono::seconds duration = std::chrono::seconds(10);

private:
    float timeBeforeMoving;
    float timeBeforeShot;

public:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    int nHealth, nKills;
    bool bEnemySpeedUp;
    bool bEnemySpeedDown;
    bool bEnemyInvBase;

public:
    Enemy(const float &x, const float &y);
    Enemy(const Enemy &copy) : Enemy(copy.mX, copy.mY){}

    void move(const sf::Int64 &time);
    void shoot(const float &time);
    void update(const sf::Int64 &time, Map &map, const bool &collision);
    void speedUp();
    void speedDown();
    void invinciBase();
    void setPosition(float fX, float fY);
};
