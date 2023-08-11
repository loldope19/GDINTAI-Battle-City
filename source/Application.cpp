//#include <SFML/Window/Event.hpp>
#include "../include/Application.h"

Application::Application()
    : mWindow(sf::VideoMode(720, 672), "Battle City"), gameOver(false), gameStarted(false),
    msgStart(90, 330, "Press \'Enter\' to start"), msgOver(250, 300, "Game over"),
    msgLost(260, 350, "You lost"), msgWon(265, 350, "You won"), msgDraw(300, 350, "DRAW!"),
    frags(0) {

    // Enemy Tank
    pEnemy = new Enemy(432, 24);

    pEnemy->nKills = 0;
    mPlayer.nKills = 0;
    
    msgEnemyKills = new Message(48, 8, "Kills: " + std::to_string(pEnemy->nKills));
    msgPlayerKills = new Message(48, 650, "Kills: " + std::to_string(mPlayer.nKills));
    
    msgTimer = new Message(600, 8, "00:00");
    msgEnemyKills->mStr.setCharacterSize(15);
    msgPlayerKills->mStr.setCharacterSize(15);
    msgTimer->mStr.setCharacterSize(15);

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

    sf::Clock clock;
    sf::Time elapsed;

    while (mWindow.isOpen()) {
        sf::Int64 time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;

        process_events();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            gameStarted = true;
            startTime = cClock.now();
            timerStartTime = std::chrono::high_resolution_clock::now();
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

            case sf::Event::MouseButtonPressed:

                break;

            case sf::Event::MouseButtonReleased:
                break;
        }
    }
}

void Application::update(const sf::Int64 &time) {
    if (gameStarted && !gameOver)
        msgTimer->setString(this->intToTime());

    if (!pEnemy->life)
        ++frags;
    else {
        frags = 0;
    }

    if (frags)
        gameOver = true;
  
    auto currentTime = cClock.now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
    auto timerElapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - timerStartTime);

    if (elapsedTime >= duration) {
        // Perform actions that should happen after 15 seconds
        srand(std::time(0));
        int nX, nY, nPowerType;
        do {
            nX = 2 + (int)std::rand() % 26;
            nY = 1 + (int)std::rand() % 26;
        } while (map.get_tile(nY, nX) != ' ' ||
                 map.get_tile(nY + 1, nX) != ' ' ||
                 map.get_tile(nY, nX + 1) != ' ' ||
                 map.get_tile(nY + 1, nX + 1) != ' ');
        
        pPower = new Powers(nX * 24, nY * 24, (int)std::rand() % 5);
        vecPowers.push_back(pPower);
        startTime = currentTime;
    }

    if (timerElapsedTime >= timerDuration) {
        gameOver = true;
    }

    bool collision;
    collision = mPlayer.mSprite.getGlobalBounds().intersects(pEnemy->mSprite.getGlobalBounds());

    if (mPlayer.life) {
        mPlayer.update(time, map, collision);

        // PLAYER Power-Up Effects
        int i = 0;
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
                        if (pEnemy->mSprite.getGlobalBounds().intersects(sf::FloatRect(224, 600, 48, 48))) {
                            mPlayer.setPosition(432, 600);
                        }
                        else {
                            mPlayer.setPosition(224, 600);
                        }
                        break;

                    case Powers::PowerType::CHAOS:
                        this->shuffleBase();
                        break;
                }
                mPlayer.startTime = std::chrono::high_resolution_clock::now();
                pPowers->life = false;
                vecPowers.erase(vecPowers.begin() + i);
            }
            i++;
        }
        
    }
    else
        gameOver = true;

    // If PLAYER steps on ENEMY BASE
    int i = 0;
    for (Base* cBase : vecBase) {
        if (mPlayer.mSprite.getGlobalBounds().intersects(cBase->mSprite.getGlobalBounds())
            && (cBase->bType == Base::BaseType::ENEMY && !cBase->bInvincible)) {
            cBase->life = false;
            pEnemy->nHealth--;
            vecBase.erase(vecBase.begin() + i);
        }
        i++;
    }

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
        Base* pBase = *vecBase.begin();     // Player Base, always pushed first so we can just get the first thing on the vector
        for (Base* pBase2 : vecBase) {
            if (pBase2->bType == Base::BaseType::ENEMY) {
                // Find an enemy base
                pEnemy->update(time, map, collision, mPlayer.getPosition(), pBase->getPosition(), pBase2->getPosition());
                break;
            }
        }

        // ENEMY Power-Up Effects
        int j = 0;
        for (Powers* pPowers : vecPowers) {
            if (pEnemy->mSprite.getGlobalBounds().intersects(pPowers->mSprite.getGlobalBounds())) {
                switch (pPowers->pType) {
                    case Powers::PowerType::SPEED_UP:
                        pEnemy->bEnemySpeedUp = true;
                        break;
                    case Powers::PowerType::SPEED_DOWN:
                        pEnemy->bEnemySpeedDown = true;
                        break;
                    case Powers::PowerType::INVINCI_BASE: {
                        pEnemy->bEnemyInvBase = true;
                        for (Base* pBase : vecBase) {
                            if (pBase->bType == Base::BaseType::ENEMY)
                                pBase->startTime = std::chrono::high_resolution_clock::now();
                        }
                    }
                        break;
                    case Powers::PowerType::MINES:
                        if (mPlayer.mSprite.getGlobalBounds().intersects(sf::FloatRect(sf::Vector2f(432, 24), sf::Vector2f(48, 48)))) {
                            pEnemy->setPosition(224, 24);
                        }
                        else 
                            pEnemy->setPosition(432, 24);

                        break;

                    case Powers::PowerType::CHAOS:
                        this->shuffleBase();
                        break;
                }
                pEnemy->startTime = std::chrono::high_resolution_clock::now();
                pPowers->life = false;
                vecPowers.erase(vecPowers.begin() + j);
            }
            j++;
        }

        // If ENEMY shoots PLAYER
        if (pEnemy->bullet.mSprite.getGlobalBounds().intersects(mPlayer.mSprite.getGlobalBounds())
            && pEnemy->bullet.present) {
            

            if (pEnemy->mSprite.getGlobalBounds().intersects(sf::FloatRect(224, 600, 48, 48))) {
                mPlayer.setPosition(432, 600);
            }
            else {
                mPlayer.setPosition(224, 600);
            }

            pEnemy->nKills++;
            msgEnemyKills->setString("Kills: " + std::to_string(pEnemy->nKills));
            pEnemy->bullet.present = false;
        }

        // If ENEMY steps on PLAYER BASE
        int i = 0;
        for (Base* cBase : vecBase) {
            if (pEnemy->mSprite.getGlobalBounds().intersects(cBase->mSprite.getGlobalBounds())
                && (cBase->bType == Base::BaseType::PLAYER && !cBase->bInvincible)) {
                cBase->life = false;
                mPlayer.nHealth--;
                vecBase.erase(vecBase.begin() + i);
            }
            i++;
        }

        // If PLAYER shoots ENEMY
        if (mPlayer.bullet.mSprite.getGlobalBounds().intersects(pEnemy->mSprite.getGlobalBounds())
            && mPlayer.bullet.present) {
            
            
            if (mPlayer.mSprite.getGlobalBounds().intersects(sf::FloatRect(sf::Vector2f(432, 24), sf::Vector2f(48, 48)))) {
                pEnemy->setPosition(224, 24);
            }
            else 
                pEnemy->setPosition(432, 24);
            mPlayer.nKills++;
            msgPlayerKills->setString("Kills: " + std::to_string(mPlayer.nKills));
            mPlayer.bullet.present = false;
        }
    }

    if (mPlayer.nHealth <= 0)
        gameOver = true;
    
    if (pEnemy->nHealth <= 0)
        gameOver = true;
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

    if (gameStarted) {
        msgEnemyKills->print(mWindow);
        msgPlayerKills->print(mWindow);
        msgTimer->print(mWindow);
    }

    if (gameOver) {
        msgOver.print(mWindow);

        if (mPlayer.nHealth < pEnemy->nHealth || mPlayer.nHealth == 0)
            msgLost.print(mWindow);
        else if (pEnemy->nHealth < mPlayer.nHealth || pEnemy->nHealth == 0)
            msgWon.print(mWindow);
        else {
            if (mPlayer.nKills > pEnemy->nKills)
                msgWon.print(mWindow);
            else if (mPlayer.nKills < pEnemy->nKills)
                msgLost.print(mWindow);
            else
                msgDraw.print(mWindow);
        }
    }

    mWindow.display();
}

void Application::shuffleBase() {
    for (Base* pBase : vecBase) {
        int nX, nY;
        bool bCollide = false;

        do {
            bCollide = false;
            nX = 2 + (int)std::rand() % 26;
            nY = 1 + (int)std::rand() % 26;
            for (Base* pBase2 : vecBase) {
                if (pBase2->mSprite.getGlobalBounds().intersects(sf::FloatRect(nX, nY, 48, 48)))
                    bCollide = true;
            }
            
        } while (map.get_tile(nY, nX) != ' ' ||
                map.get_tile(nY + 1, nX) != ' ' ||
                map.get_tile(nY, nX + 1) != ' ' ||
                map.get_tile(nY + 1, nX + 1) != ' ' ||
                bCollide != false);

        pBase->setPosition(nX * 24, nY * 24);
    }
}

sf::String Application::intToTime() {
    auto currentTime = cClock.now();
    auto timerElapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - timerStartTime);

    int totalSeconds = static_cast<int>(timerElapsedTime.count());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::ostringstream formattedTime;
    formattedTime << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds;

    return formattedTime.str();
}