#include "Collisionable.h"

using namespace controllers;

Collisionable::Collisionable(GameSprite& cSprite, Map& cMap, bool bPlayer, int ID, Move cMove) :
    bExists(true), cSprite(cSprite), cMap(cMap), bPlayer(bPlayer), objID(ID) {}

Collisionable::~Collisionable(void) {}

void Collisionable::checkCollision(std::list<TankPtr>& tanks, std::list<Bullet>& bullets) {
    if (cTimer.getElapsedTime().asSeconds() >= fSpeed) {
        if (cMove != Move::NONE) {
            sf::FloatRect box = sSprite.getGlobalBounds();

            posMap.x = (sSprite.getPosition().x - cMap.sScreen.nSides) / cMap.sScreen.nBlockSize;
            posMap.y = (sSprite.getPosition().y - cMap.sScreen.topBot) / cMap.sScreen.nBlockSize;

            float speed = cMap.sScreen.nBlockSize / 4.f;

            this->updateImage();

            bool bCol = false;

            switch (cMove) {
                case Collisionable::Move::LEFT:
                    box.left -= speed;
                    posMap.x--;
                    if (collision(posMap, box))
                        bCol = true;
                    posMap.y++;
                    if (collision(posMap, box))
                        bCol = true;
                    posMap.y++;
                    if (collision(posMap, box))
                        bCol = true;
                    if (bCol)
                        return;
                    break;
                
                case Collisionable::Move::RIGHT:
                    box.left += speed;
                    posMap.x += 2;
                    if (collision(posMap, box))
                        bCol = true;
                    posMap.y++;
                    if (collision(posMap, box))
                        bCol = true;
                    posMap.y++;
                    if (collision(posMap, box))
                        bCol = true;
                    if (bCol)
                        return;
                    break;
                
                case Collisionable::Move::UP:
                    box.top -= speed;
                    posMap.y--;
                    if (collision(posMap, box))
                        bCol = true;
                    posMap.x++;
                    if (collision(posMap, box))
                        bCol = true;
                    posMap.x++;
                    if (collision(posMap, box))
                        bCol = true;
                    if (bCol)
                        return;
                    break;
                
                case Collisionable::Move::DOWN:
                    box.top -= speed;
                    posMap.y += 2;
                    if (collision(posMap, box))
                        bCol = true;
                    posMap.x++;
                    if (collision(posMap, box))
                        bCol = true;
                    posMap.x++;
                    if (collision(posMap, box))
                        bCol = true;
                    if (bCol)
                        return;
                    break;
            }

            if (collideWithTanks(tanks, bullets, speed))
                return;
            
            vecPosition.x = box.left;
            vecPosition.y = box.top;
            sSprite.setPosition(box.left, box.top);

            cTimer.restart();
        }
    }
    sSprite.setPosition(vecPosition);
}
