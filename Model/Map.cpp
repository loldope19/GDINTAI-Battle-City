#include "Map.h"

using namespace models;
extern Sound sound;

Map::Map(GameSprite& pSprite, Timer& cFPSClock, sf::RenderWindow& rwWindow) : cSprite(pSprite), cGameClock(cFPSClock), rwWindow(rwWindow) {
    sPlayerTank = pSprite.greenTankSprite;
    sEnemyTank = pSprite.redTankSprite;

    sPlayerTank.setTextureRect(sf::IntRect(200, 0, 100, 100));
    sPlayerTank.setPosition(1200.f, 800.f);
    sEnemyTank.setTextureRect(sf::IntRect(200, 0, 100, 100));
    sEnemyTank.setPosition(1200.f, 500.f);

    this->setInformationProperties();
}

models::Map::~Map(){}

int Map::loadMap() {
    int nType, nSet;

    if (cLevel.nLevelCount == 7) {
        this->win();
        return 0;
    }
    else {
        if (cLevel.nLevelCount == 1) {
            cGameClock.restart();
            cGameClock.toggleClock();
        }

        for (auto& tank : cLevel.Tanks) {
            if (tank->player)
                tank->InitialPlace();
        }

        cLevel.nPlayerTanks = 3;

        std::string path = "View/Levels/level" + std::to_string(cLevel.nLevelCount) + ".txt";
        std::ifstream fFile(path, std::ios::in);

        fFile >> cLevel.nEnemyTanks;
        nAliveEnemyTank >> cLevel.nEnemyTanks;

        for (int y = 0; y < nBlockSize / 2; y++) {
            for (int x = 0, X = x * 2, Y = y * 2; x < nBlockSize / 2; x++, X = x * 2, Y = y * 2) {
                fFile >> nType >> nSet;

                cTab[Y][X].pos = Block::Pos::POS1;
                cTab[Y][X + 1].pos = Block::Pos::POS2;
                cTab[Y + 1][X + 1].pos = Block::Pos::POS3;
                cTab[Y + 1][X].pos = Block::Pos::POS4;

                switch (Map::Set(nSet)) {
                    case Map::Set::LEFT:
                        cTab[Y][X].type = cTab[Y + 1][X].type = Block::Type(type);
                        cTab[Y][X + 1].type
                }
            }
        }
        
    }
}
