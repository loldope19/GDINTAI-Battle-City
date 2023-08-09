#include "Single.h"

using namespace models;

Single::Single(bool bGameType, sf::Font& font, Map& cMap, GameSprite& cSprite, sf::RenderWindow& rwWindow, Timer& cFPSClock)
    : bGameType(bGameType), cFont(font), cMap(cMap), cSprite(cSprite), rwWindow(rwWindow), cFPSClock(cFPSClock) {}

Single::~Single() {}

void Single::runSingle() {
    cMap.initiateGame(bGameType);
    cFPSClock.stopClock();
    while (cMap.gameGood()) {
        if (cMap.loadMap() == 0)
            continue;
        
        while (cMap.checkGameStatus()) {
            cSound.updateSound(cMap.cLevel.Tanks);

            cMap.events(cFPSClock);

            cMap.addPlayer1Tank();
            if (bGameType)
                cMap.addPlayer2Tank();
            cMap.addEnemyTank();

            for (auto& Tank : cMap.cLevel.Tanks) {
                Tank->checkMove();
                Tank->checkCollision(cMap.cLevel.Tanks, cMap.cLevel.Bullets);
            }
            for (auto& Bullet : cMap.cLevel.Bullets) {
                Bullet->checkCollision(cMap.cLevel.Tanks, cMap.cLevel.Bullets);
            }

            clearDeadObjects();

            rwWindow.clear();

            for (auto& Tank : cMap.cLevel.Tanks) {
                rwWindow.draw(*Tank);
            }

            rwWindow.draw(cMap);

            for (auto& Bullet : cMap.cLevel.Bullets) {
                rwWindow.draw(Bullet);
            }

            for (auto& Ded : cMap.cLevel.Explosions) {
                rwWindow.draw(Ded);
            }

            cFPSClock.draw(rwWindow);
            cMap.setInformationProperties();
            rwWindow.display();
        }
    }
    cFPSClock.stopClock();
    cSound.stopAll();
    cMap.endGame();
}

void Single::clearDeadObjects() {
    for (auto Bullet : cMap.cLevel.Bullets) {
        if (Bullet.exist == false) {
            for (auto& Tank : cMap.cLevel.Tanks) {
                if (Bullet.objID == Tank->objID) {
                    Tank->canShoot = true;
                    break;
                }
            }
        }
    }

    BACK:

    for (auto i = cMap.cLevel.Bullets.begin(); i != cMap.cLevel.Bullets.end(); i++) {
        if (i->exist == false) {
            cMap.cLevel.Bullets.erase(i);
            goto BACK;
        }
    }

    cMap.cLevel.Tanks.erase(std::remove_if(cMap.cLevel.Tanks.begin(), cMap.cLevel.Tanks.end(),
        [&](const TankPtr &x)->bool{return x->exist == false;}), cMap.cLevel.Tanks.end());

    cMap.cLevel.Explosions.erase(std::remove_if(cMap.cLevel.Explosions.begin(), cMap.cLevel.Explosions.end(),
        [&](Explosion &x)->bool{return x.stillExist() == false;}), cMap.cLevel.Explosions.end());
}