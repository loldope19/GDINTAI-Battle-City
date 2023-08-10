//#include <SFML/Window/Event.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "../include/Application.h"

Application::Application()
    : mWindow(sf::VideoMode(720, 672), "Battle City"), gameOver(false), gameStarted(false),
    msgStart(90, 330, "Press \'Enter\' to start"), msgOver(250, 300, "Game over"),
    msgLost(260, 350, "You lost"), msgWon(265, 350, "You won"), frags(0) {

    sf::Clock clock;

    packOfEnemies = new Enemy[4]{ Enemy(52,31), Enemy(147,391), Enemy(532,391), Enemy(628,31) };

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
    for (int i(0); i < 4; ++i)
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
    for (int i(0); i < 4; ++i) {
        collision = mPlayer.mSprite.getGlobalBounds().intersects(packOfEnemies[i].mSprite.getGlobalBounds());
        if (collision)
            break;
    }

    if (mPlayer.life)
        mPlayer.update(time, map, collision);

    for (int i(0); i < 4; ++i) {
        if (packOfEnemies[i].life) {
            packOfEnemies[i].update(time, map, collision);

            if (packOfEnemies[i].bullet.mSprite.getGlobalBounds().intersects(mPlayer.mSprite.getGlobalBounds())
                && packOfEnemies[i].bullet.present) {
                mPlayer.collapse();
                packOfEnemies[i].bullet.present = false;
            }

            if (packOfEnemies[i].bullet.mSprite.getGlobalBounds().intersects(mBase.mSprite.getGlobalBounds())
                && packOfEnemies[i].bullet.present) {
                mBase.life = false;
                gameOver = true;
            }
            if (mPlayer.bullet.mSprite.getGlobalBounds().intersects(packOfEnemies[i].mSprite.getGlobalBounds())
                && mPlayer.bullet.present) {
                packOfEnemies[i].collapse();
                mPlayer.bullet.present = false;
            }
        }
    }

    if (mPlayer.bullet.mSprite.getGlobalBounds().intersects(mBase.mSprite.getGlobalBounds())
        && mPlayer.bullet.present) {
        mBase.life = false;
        gameOver = true;
    }
}

void Application::render() {
    mWindow.clear();

    map.draw(mWindow);
    if (mPlayer.life)
        mWindow.draw(mPlayer.mSprite);
    if (mPlayer.bullet.present) mWindow.draw(mPlayer.bullet.mSprite);

    for (int i(0); i < 4; ++i) {
        if (packOfEnemies[i].bullet.present)
            mWindow.draw(packOfEnemies[i].bullet.mSprite);

        if (packOfEnemies[i].life)
            mWindow.draw(packOfEnemies[i].mSprite);
    }

    if (mBase.life)
        mWindow.draw(mBase.mSprite);

    if (!gameStarted)
        msgStart.print(mWindow);

    if (gameOver) {
        msgOver.print(mWindow);
        if (!mBase.life || !mPlayer.life)

            msgLost.print(mWindow);
        else
            msgWon.print(mWindow);
    }

    mWindow.display();
}
