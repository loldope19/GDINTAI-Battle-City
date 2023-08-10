//#include <SFML/Window/Event.hpp>

#include <iostream>
#include "../include/Application.h"

Application::Application()
    : mWindow(sf::VideoMode(720, 672), "Battle City"), gameOver(false), gameStarted(false),
    msgStart(90, 330, "Press \'Enter\' to start"), msgOver(250, 300, "Game over"),
    msgLost(260, 350, "You lost"), msgWon(265, 350, "You won"), frags(0) {

    sf::Clock clock;

    packOfEnemies = new Enemy[1]{ /*Enemy(52,31),*/ Enemy(147,391)/*, Enemy(532,391), Enemy(628,31) */};

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            gameStarted = true;

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
    for (int i(0); i < 1; ++i)
        if (!packOfEnemies[i].life)
            ++frags;
        else {
            frags = 0;
            break;
        }

    if (frags == 4)
        gameOver = true;

    if (!mPlayer.life)
        gameOver = true;

    bool collision;
    for (int i(0); i < 1; ++i) {
        collision = mPlayer.mSprite.getGlobalBounds().intersects(packOfEnemies[i].mSprite.getGlobalBounds());
        if (collision)
            break;
    }

    if (mPlayer.life)
        mPlayer.update(time, map, collision);

    for (int i(0); i < 1; ++i) {
        if (packOfEnemies[i].life) {
            packOfEnemies[i].update(time, map, collision);

            if (packOfEnemies[i].bullet.mSprite.getGlobalBounds().intersects(mPlayer.mSprite.getGlobalBounds())
                && packOfEnemies[i].bullet.present) {
                mPlayer.collapse();
                packOfEnemies[i].bullet.present = false;
            }

            for (Base* cBase : vecBase) {
                if (packOfEnemies[i].bullet.mSprite.getGlobalBounds().intersects(cBase->mSprite.getGlobalBounds())
                    && packOfEnemies[i].bullet.present && cBase->bType == Base::BaseType::PLAYER) {
                    cBase->life = false;
                    gameOver = true;
                }
            }

            if (mPlayer.bullet.mSprite.getGlobalBounds().intersects(packOfEnemies[i].mSprite.getGlobalBounds())
                && mPlayer.bullet.present) {
                packOfEnemies[i].collapse();
                mPlayer.bullet.present = false;
            }
        }
    }

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
    if (mPlayer.bullet.present) mWindow.draw(mPlayer.bullet.mSprite);

    for (int i(0); i < 1; ++i) {
        if (packOfEnemies[i].bullet.present)
            mWindow.draw(packOfEnemies[i].bullet.mSprite);

        if (packOfEnemies[i].life)
            mWindow.draw(packOfEnemies[i].mSprite);
    }

    for (Base* cBase : vecBase) {
        if (cBase->life)
            mWindow.draw(cBase->mSprite);
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
