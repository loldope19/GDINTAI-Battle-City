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
    std::chrono::high_resolution_clock::time_point timerStartTime;
    const std::chrono::seconds timerDuration{120};  // 2 Mins
    
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
    Message msgDraw;
    Message* msgTimer;
    Message* msgPlayerKills;
    Message* msgEnemyKills;

public:
    Application();

    void process_events();
    void update(const sf::Int64 &time);
    void render();

    void shuffleBase();
    sf::String intToTime();
};
