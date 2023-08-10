#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "Tank.h"

class Player : public Tank {
private:
    std::chrono::high_resolution_clock cClock;
    std::chrono::seconds duration = std::chrono::seconds(10);
    
    float initialSpeed = 0.12f;
    int nHealth;
    int nKills;

public:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    bool bPlayerSpeedUp;
    bool bPlayerSpeedDown;
    bool bPlayerInvBase;
    bool bPlayerMine;

public:
    Player();

    void move(const sf::Int64 &time);
    void update(const sf::Int64 &time, Map &map, const bool &collision);
    void speedUp();
    void speedDown();
    void invinciBase();
};
