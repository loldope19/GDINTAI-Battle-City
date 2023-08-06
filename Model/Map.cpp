#include "Map.h"

/*
using namespace models;
extern Sound sound;

Map::Map(Sprite& pSprite, Timer& cFPSClock, sf::RenderWindow& rwWindow) : cSprite(pSprite), cGameClock(cFPSClock), rwWindow(rwWindow) {
    sPlayerTank = pSprite.greenTankSprite;
    sEnemyTank = pSprite.redTankSprite;

    sPlayerTank.setTextureRect(sf::IntRect(200, 0, 100, 100));
    sPlayerTank.setPosition(1200.f, 800.f);
    sEnemyTank.setTextureRect(sf::IntRect(200, 0, 100, 100));
    sEnemyTank.setPosition(1200.f, 500.f);

    this->setInformationProperties();
}

Map::~Map();

int Map::loadMap() {
    int nType, nSet;

    if (sLevel.nLevelCount == 1) {
        cGameClock.restart();
        cGameClock.toggleClock();
    }

    for (auto& tank : sLevel.Tanks) {
        if (tank->player)
            tank->InitialPlace();
    }

}
*/