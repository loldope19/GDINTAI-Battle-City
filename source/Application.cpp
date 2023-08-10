//#include <SFML/Window/Event.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include "../include/Application.h"

Application::Application()
    : mWindow(sf::VideoMode(720, 672), "Battle City"), gameOver(false), gameStarted(false),
    msgStart(90, 330, "Press \'Enter\' to start"), msgOver(250, 300, "Game over"),
    msgLost(260, 350, "You lost"), msgWon(265, 350, "You won"), frags(0) {
    
    

    sf::Clock clock;
    sf::Time elapsed;

    // Enemy Tank
    pEnemy = new Enemy(147, 391);

    // PLAYER BASES
    mBase = new Base(336, 600, Base::BaseType::PLAYER);
    vecBase.push_back(mBase);

    mBase = new Base(48, 384, Base::BaseType::PLAYER);
    vecBase.push_back(mBase);

    mBase = new Base(528, 504, Base::BaseType::PLAYER);
    vecBase.push_back(mBase);    

    // ENEMY BASES
    mBase = new Base(336, 24, Base::BaseType::ENEMY);
    vecBase.push_back(mBase);

    mBase = new Base(624, 288, Base::BaseType::ENEMY);
    vecBase.push_back(mBase);

    mBase = new Base(144, 120, Base::BaseType::ENEMY);
    vecBase.push_back(mBase);

    while (mWindow.isOpen()) {
        sf::Int64 time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;

        process_events();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            gameStarted = true;
            startTime = cClock.now();
        }

        if (gameStarted && !gameOver)
            update(time);
        render();
    }
}

void Application::process_events() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Application::update(const sf::Int64 &time) {
    if (!pEnemy->life)
        ++frags;
    else {
        frags = 0;
    }

    if (frags)
        gameOver = true;

    // If PLAYER gets killed-- (ayo go derek!!)
    if (!mPlayer.life)
        gameOver = true;
    

    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime >= duration) {
        // Perform actions that should happen after 15 seconds
        srand(std::time(0));
        int nX, nY, nPowerType;
        do {
            nX = 2 + (int)std::rand() % 26;
            nY = 1 + (int)std::rand() % 26;
            //std::cout << map.get_tile(nY, nX) << " " << map.get_tile(nY + 1, nX) << " " << map.get_tile(nY, nX + 1) << " " << map.get_tile(nY + 1, nX + 1) << std::endl;
        } while (map.get_tile(nY, nX) != ' ' &&
                 map.get_tile(nY + 1, nX) != ' ' &&
                 map.get_tile(nY, nX + 1) != ' ' &&
                 map.get_tile(nY + 1, nX + 1) != ' ');
        
        pPower = new Powers(nX * 24, nY * 24, (int)std::rand() % 5);
        vecPowers.push_back(pPower);
        startTime = currentTime;
    }

    bool collision;
    collision = mPlayer.mSprite.getGlobalBounds().intersects(pEnemy->mSprite.getGlobalBounds());

    if (mPlayer.life) {
        mPlayer.update(time, map, collision);

        for (Powers* pPowers : vecPowers) {
            if (mPlayer.mSprite.getGlobalBounds().intersects(pPowers->mSprite.getGlobalBounds())) {
                switch (pPowers->pType) {
                    case Powers::PowerType::SPEED_UP:
                        mPlayer.bPlayerSpeedUp = true;
                        break;
                    case Powers::PowerType::SPEED_DOWN:
                        mPlayer.bPlayerSpeedDown = true;
                        break;
                    case Powers::PowerType::INVINCI_BASE: {
                        mPlayer.bPlayerInvBase = true;
                        for (Base* pBase : vecBase) {
                            if (pBase->bType == Base::BaseType::PLAYER)
                                pBase->startTime = std::chrono::high_resolution_clock::now();
                        }
                    }
                        break;
                    case Powers::PowerType::MINES:
                        for (Tank )
                        break;
                    case Powers::PowerType::CHAOS:
                        break;
                }
                mPlayer.startTime = std::chrono::high_resolution_clock::now();
                pPowers->life = false;
            }
        }
        
    }
    else
        gameOver = true;

    if (mPlayer.bPlayerSpeedUp) {
        mPlayer.speedUp();
    }

    if (mPlayer.bPlayerSpeedDown) {
        mPlayer.speedDown();
    }

    if (mPlayer.bPlayerInvBase) {
        mPlayer.invinciBase();
        for (Base* pBase : vecBase) {
            if (pBase->bType == Base::BaseType::PLAYER)
                pBase->invincible();
        }
    }

    if (pEnemy->life) {
        pEnemy->update(time, map, collision);

        if (pEnemy->bullet.mSprite.getGlobalBounds().intersects(mPlayer.mSprite.getGlobalBounds())
            && pEnemy->bullet.present) {
            mPlayer.collapse();
            pEnemy->bullet.present = false;
        }

        // If ENEMY shoots PLAYER BASE
        for (Base* cBase : vecBase) {
            if (pEnemy->bullet.mSprite.getGlobalBounds().intersects(cBase->mSprite.getGlobalBounds())
                && pEnemy->bullet.present && (cBase->bType == Base::BaseType::PLAYER)) {
                cBase->life = false;
                gameOver = true;
            }
        }

        // If PLAYER shoots ENEMY
        if (mPlayer.bullet.mSprite.getGlobalBounds().intersects(pEnemy->mSprite.getGlobalBounds())
            && mPlayer.bullet.present) {
            pEnemy->collapse();
            mPlayer.bullet.present = false;
        }
    }

    // If PLAYER shoots ENEMY BASE
    for (Base* cBase : vecBase) {
        if (mPlayer.bullet.mSprite.getGlobalBounds().intersects(cBase->mSprite.getGlobalBounds())
            && mPlayer.bullet.present && cBase->bType == Base::BaseType::ENEMY) {
            cBase->life = false;
            gameOver = true;
        }
    }
    
}

void Application::render() {
    mWindow.clear();

    map.draw(mWindow);
    if (mPlayer.life)
        mWindow.draw(mPlayer.mSprite);

    if (mPlayer.bullet.present) 
        mWindow.draw(mPlayer.bullet.mSprite);

    for (int i(0); i < 1; ++i) {
        if (pEnemy->bullet.present)
            mWindow.draw(pEnemy->bullet.mSprite);

        if (pEnemy->life)
            mWindow.draw(pEnemy->mSprite);
    }

    for (Base* cBase : vecBase) {
        if (cBase->life)
            mWindow.draw(cBase->mSprite);
    }

    for (Powers* pPowers : vecPowers) {
        if (pPowers->life)
            mWindow.draw(pPowers->mSprite);
    }

    if (!gameStarted)
        msgStart.print(mWindow);

    if (gameOver) {
        msgOver.print(mWindow);
        //if (!mBase.life || !mPlayer.life)

        //    msgLost.print(mWindow);
        //else
            msgWon.print(mWindow);
    }

    mWindow.display();
}
