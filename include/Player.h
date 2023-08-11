#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include "Tank.h"

class Player : public Tank {
private:
    std::chrono::high_resolution_clock cClock;
    std::chrono::seconds duration = std::chrono::seconds(10);
    
    float initialSpeed = 0.12f;

public:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    int nHealth;
    int nKills;
    bool bPlayerSpeedUp;
    bool bPlayerSpeedDown;
    bool bPlayerInvBase;

public:
    Player();

    void move(const sf::Int64 &time);
    void update(const sf::Int64 &time, Map &map, const bool &collision);
    void speedUp();
    void speedDown();
    void invinciBase();
    void setPosition(float fX, float fY);
};
