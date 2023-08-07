#include "Tank.h"

using namespace models;

Tank::Tank(std::list<Explosion>& Explosions, std::list<Bullet> Bullets, GameSprite& cSprite, Map& cMap, bool bIsPlayer, int ID, Move cMove)
    : Collisionable(cSprite, cMap, bIsPlayer, ID, cMove), Bullets(Bullets), Explosions(Explosions) {
    
}

Tank::~Tank(void) {
    if (bExists == false)
        Explosions.push_back(Explosion(cMap, *this));
}

void Tank::draw(sf::RenderTarget& rtWindow, sf::RenderStates rStates) const {
    rtWindow.draw(sSprite);
}

bool Tank::collision(Pos PosMap, sf::FloatRect& sfBox) {
    Block cBlock = cMap.cTab[PosMap.y][PosMap.x];

    if (sfBox.intersects(cBlock.cImg.getGlobalBounds())) {
        if (cBlock.move == Block::Move::NOT_MOVEABLE ||
            cBlock.move == Block::Move::WATER ||
            cBlock.move == Block::Move::ENDMAP) {
            
            sSprite.setPosition(vecPosition);
            cMove = Move::NONE;
        }
    }
}

bool Tank::collideWithTanks(std::list<TankPtr>& Tanks, std::list<Bullet>& Bullets, float fSpeed) {
    sf::FloatRect sfBox = this->sSprite.getGlobalBounds();

    switch (this->cMove) {
        case Tank::Move::LEFT:
            sfBox.left -= fSpeed;
            break;
        case Tank::Move::RIGHT:
            sfBox.left += fSpeed;
            break;
        case Tank::Move::UP:
            sfBox.top -= fSpeed;
            break;
        case Tank::Move::DOWN:
            sfBox.top += fSpeed;
            break;
    }

    for (auto& Tank : Tanks) {
        if (this->objID != Tank->objID) {
            if (sfBox.intersects(Tank->sSprite.getGlobalBounds())) {
                this->sSprite.setPosition(vecPosition);
                this->cMove = Move::NONE;
                return true;
            }
        }
    }

    return false;
}

void Tank::updateImage() {
    switch (cMove) {
        case Collisionable::Move::LEFT:
            sSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
            break;
        
        case Collisionable::Move::RIGHT:
            sSprite.setTextureRect(sf::IntRect(100, 0, 100, 100));
            break;
        
        case Collisionable::Move::UP:
            sSprite.setTextureRect(sf::IntRect(200, 0, 100, 100));
            break;
        
        case Collisionable::Move::DOWN:
            sSprite.setTextureRect(sf::IntRect(300, 0, 100, 100));
            break;
    }
}

bool Tank::spawnCollision(std::list<TankPtr>& Tanks) {
    sf::FloatRect sfBox = this->sSprite.getGlobalBounds();

    for (auto& Tank : Tanks) {
        if (this->objID != Tank->objID) {
            if (sfBox.intersects(Tank->sSprite.getGlobalBounds())) {
                this->sSprite.setPosition(vecPosition);
                cMove = Move::NONE;
                return true;
            }
        }
    }
    return false;
}