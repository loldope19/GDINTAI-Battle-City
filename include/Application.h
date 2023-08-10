#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Base.h"
#include "Message.h"
#include "Powers.h"

class Application : private sf::NonCopyable {
private:
    std::chrono::high_resolution_clock cClock;
    std::chrono::seconds duration = std::chrono::seconds(5);
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    
    bool gameOver;
    bool gameStarted;

    int frags;

    sf::RenderWindow mWindow;
    std::vector<Base*> vecBase;
    std::vector<Powers*> vecPowers;
    Base* mBase;
    Map map;
    Player mPlayer;
    Enemy* pEnemy;
    Powers* pPower;

    Message msgStart;
    Message msgOver;
    Message msgLost;
    Message msgWon;

public:
    bool bEnemySpeedUp;
    bool bEnemySpeedDown;
    bool bEnemyInvBase;
    bool bEnemyMine;

public:
    Application();

    void process_events();
    void update(const sf::Int64 &time);
    void render();
};
