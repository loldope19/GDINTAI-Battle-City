#include "Enemy.h"

using namespace models;

Enemy::Enemy(std::list<Explosion>& Explosions, std::list<Bullet>& Bullets, GameSprite& cSprite, Map& cMap, int objID, Level::newTankPos tankPos, bool bIsPlayer, Move CMove)
    : Tank(Explosions, Bullets, cSprite, cMap, bIsPlayer, objID, CMove) {
    bIsPlayer = false;
    CMove = Move::DOWN;
    
    fSpeed = EnemySpeed;

    if (std::rand() % 2) {
        sSprite = cSprite.greyTankSprite;
    }
    else {
        sSprite = cSprite.redTankSprite;
    }

    switch (tankPos) {
        case Level::newTankPos::LEFT:
            vecPosition.x = cMap.sScreen.nSides + cMap.sScreen.nBlockSize * 2;
            vecPosition.y = cMap.sScreen.topBot + cMap.sScreen.nBlockSize;
            break;
        
        case Level::newTankPos::MID:
            vecPosition.x = cMap.sScreen.nSides + cMap.sScreen.nBlockSize * 14;
            vecPosition.y = cMap.sScreen.topBot + cMap.sScreen.nBlockSize;
            break;
        
        case Level::newTankPos::RIGHT:
            vecPosition.x = cMap.sScreen.nSides + cMap.sScreen.nBlockSize * 26;
            vecPosition.y = cMap.sScreen.topBot + cMap.sScreen.nBlockSize;
            break;
    }

    sSprite.setPosition(vecPosition.x, vecPosition.y);
    sSprite.setScale(cMap.sScreen.nScale, cMap.sScreen.nScale);

    this->updateImage();

    cLastMove = cMove;
}

void Enemy::checkMove() {
    if (cMove = Move::NONE) {
        cLastMove = cMove = Move(rand() % 4);
    }

    if (bCanShoot && std::rand % 100 == false) {
        Bullets.emplace_back(cSprite, cMap, vecPosition, objID, lastMove, bIsPlayer);
        bCanShoot = false;
    }
}