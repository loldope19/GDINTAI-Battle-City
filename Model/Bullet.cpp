#include "Bullet.h"

using namespace models;

extern Sound cSound;

Bullet::Bullet(GameSprite& cSprite, Map& cMap, sf::Vector2f vecPosition, int objID, Move cMove, bool bIsPlayer)
    : Collisionable(cSprite, cMap, bIsPlayer, objID, cMove) 
{
    fSpeed = BulletSpeed;

    this->cSprite - cSprite.bulletSprite;

    this->updateImage();
    this->setStartPos(vecPosition);
}

void Bullet::draw(sf::RenderTarget& rtWindow, sf::RenderStates rsStates) {
    rtWindow.draw(sSprite);
}

bool Bullet::collision(Pos PosMap, sf::FloatRect& sRect) {
    Block collisionBlock = cMap.cTab[PosMap.y][PosMap.x];

    if (sRect.intersects(collisionBlock.cImg.getGlobalBounds())) {
        if (collisionBlock.cMove == Block::Move::NOT_MOVEABLE) {
            if (collisionBlock.type == Block::Type::EAGLE_DEAD) {
                sSprite.setPosition(vecPosition);
                bExists = false;
                cMove = Move::NONE;
                return true;
            }
            else if (collisionBlock.type == Block::Type::EAGLE) {
                cSound.Sounds["block"].play();
                cMap.cTab[PosMap.y][PosMap.x].shotEagle(cMap);
                sSprite.setPosition(vecPosition);
                bExists = false;
                cMove = Move::NONE;
                return true;
            }
            else {
                cSound.Sounds["block"].play();
                cMap.cTab[PosMap.y][PosMap.x].shotBlock(cSprite);
                sSprite.setPosition(vecPosition);
                bExists = false;
                cMove = Move::NONE;
                return true;
            }
        }

        else if (collisionBlock.cMove == Block::Move::ENDMAP) {
            cSound.Sounds["block"].play();
            cMap.cTab[PosMap.y][PosMap.x].shotBlock(cSprite);
            bExists = false;
            cMove = Move::NONE;
            return true;
        }
    }

    return false;
}

bool Bullet::collideWithTanks(std::list<TankPtr>& Tanks, std::list<Bullet>& Bullets, float fSpeed) {
    sf::FloatRect cBox = this->sSprite.getGlobalBounds();
    switch (this->CMove) {
        case Bullet::Move::LEFT:
            cBox.left -= fSpeed;
            break;
        
        case Bullet::Move::RIGHT:
            cBox.left += fSpeed;
            break;
        
        case Bullet::Move::UP:
            cBox.top -= fSpeed;
            break;
        
        case Bullet::Move::DOWN:
            cBox.top += fSpeed;
            break;
    }

    for (auto& tank : Tanks) {
        if (cBox.intersects(tank->sSprite.getGlobalBounds())) {
            if (this->bPlayer != tank->bPlayer) {
                this->sSprite.setPosition(vecPosition);
                this->bExists = false;
                tank->bExists = false;
                return true;
            }
            else if (this->objID != tank->objID) {
                this->sSprite.setPosition(vecPosition);
                this->bExists = false;
                return true;
            }
            else {
                this->sSprite.setPosition(cBox.left, cBox.top);
                return true;
            }
        }
    }
    return collideWithBullets(Bullets, cBox);
}

void Bullet::setStartPos(sf::Vector2f vecTankPos) {
    this->sSprite.setPosition(vecTankPos.x, vecTankPos.y);
    this->sSprite.scale(cMap.sScreen.fScale);

    float fPicWidth = sSprite.getGlobalBounds().height / 2.0f;

    switch (cMove) {
        case Collisionable::Move::LEFT:
            vecTankPos.y += cMap.sScreen.nBlockSize - fPicWidth;
            break;
        case Collisionable::Move::RIGHT:
            vecTankPos.x += cMap.sScreen.nBlockSize - fPicWidth;
            vecTankPos.y += cMap.sScreen.nBlockSize - fPicWidth;
            break;
        case Collisionable::Move::UP:
            vecTankPos.x += cMap.sScreen.nBlockSize - fPicWidth;
            break;
        case Collisionable::Move::DOWN:
            vecTankPos.x += cMap.sScreen.nBlockSize - fPicWidth;
            vecTankPos.y += cMap.sScreen.nBlockSize - fPicWidth;
            break;
    }

    vecPosition.x = vecTankPos.x;
    vecPosition.y = vecTankPos.y;

    this->sSprite.setPosition(vecPosition.x, vecPosition.y);
    
}

bool Bullet::collideWithBullets(std::list<Bullet>& Bullets, sf::FloatRect& cBox) {
    for (auto aBullet = Bullets.begin(); aBullet != Bullets.end(); aBullet++) {
        if (cBox.intersects(aBullet->sSprite.getGlobalBounds())) {
            if (this->bPlayer != aBullet->bPlayer) {
                this->sSprite.setPosition(vecPosition);
                aBullet->bExists = bExists = false;
                return true;
            }
            else if (this->objID != aBullet->objID) {
                this->sSprite.setPosition(vecPosition);
                this->bExists = false;
                return true;
            }
            else {
                this->sSprite.setPosition(cBox.left, cBox.top);
                return true;
            }
        }
    }
    return false;
}

void Bullet::updateImage() {
    switch (cMove) {
        case Collisionable::Move::LEFT:
            this->sSprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
            break;
        case Collisionable::Move::RIGHT:
            this->sSprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
            break;
        case Collisionable::Move::UP:
            this->sSprite.setTextureRect(sf::IntRect(80, 0, 40, 40));
            break;
        case Collisionable::Move::DOWN:
            this->sSprite.setTextureRect(sf::IntRect(120, 0, 40, 40));
            break;
    }
}

void Bullet::checkCollision(std::list<TankPtr>& Tanks, std::list<Bullet>& Bullets) {
    if (cTimer.getElapsedTime().asSeconds() >= fSpeed) {
        if (cMove != Move::NONE) {
            sf::FloatRect cBox = sSprite.getGlobalBounds();

            posMap.x = (sSprite.getPosition().x - cMap.sScreen.nSides) / cMap.sScreen.nBlockSize;
            posMap.y = (sSprite.getPosition().y - cMap.sScreen.topBot) / cMap.sScreen.nBlockSize;

            float fSpeed2 = cMap.sScreen.nBlockSize / 4.f;

            this->updateImage();

            bool bCol = false;

            switch (cMove) {
                case Collisionable::Move::LEFT:
                    cBox.left -= fSpeed2;
                    posMap.x--;
                    if (collision(posMap, cBox)) {
                        bCol = true;
                        posMap.y++;
                    }
                    if (collision(posMap, cBox)) {
                        bCol = true;
                    }
                    break;
                
                case Collisionable::Move::RIGHT:
                    cBox.left += fSpeed2;
                    posMap.x++;
                    if (collision(posMap, cBox)) {
                        bCol = true;
                        posMap.y++;
                    }
                    if (collision(posMap, cBox)) {
                        bCol = true;
                    }
                    break;
                
                case Collisionable::Move::UP:
                    cBox.top -= fSpeed2;
                    posMap.y--;
                    if (collision(posMap, cBox)) {
                        bCol = true;
                        posMap.x++;
                    }
                    if (collision(posMap, cBox)) {
                        bCol = true;
                    }
                    break;
                
                case Collisionable::Move::DOWN:
                    cBox.top += fSpeed2;
                    posMap.y++;
                    if (collision(posMap, cBox)) {
                        bCol = true;
                        posMap.x++;
                    }
                    if (collision(posMap, cBox)) {
                        bCol = true;
                    }
                    break;
            }

            if (bCol)
                return;
            
            if (collideWithTanks(Tanks, Bullets, fSpeed2))
                return;
            
            vecPosition.x = cBox.left;
            vecPosition.y = cBox.top;
            sSprite.setPosition(cBox.left, cBox.top);

            cTimer.restart();
        }
    }
    sSprite.setPosition(vecPosition);
}