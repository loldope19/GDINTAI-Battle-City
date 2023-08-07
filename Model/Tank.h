#ifndef MODEL_TANK_H
#define MODEL_TANK_H

#include "../Controller/Collisionable.h"

#include "Map.h"

#include "../View/Sprite.h"
#include "../View/Block.h"
//#include "Explosion.h"

const int nPlayerLives = 3;

class Explosion;

namespace models {
    class Tank : public sf::Drawable, public Collisionable {
        private:
            std::list<Explosion>& Explosions;

        public:
            std::list<Bullet>& Bullets;
            bool bReadyToShoot = true;
            bool bCanShoot = true;
        
        public:
            Tank(std::list<Explosion>& Explosions, std::list<Bullet> Bullets, GameSprite& cSprite, Map& cMap, bool bIsPlayer, int ID, Move cMove);
            virtual ~Tank(void);
        
        public:
            virtual void checkMove() = 0;
            virtual bool collision(Pos, sf::FloatRect&) final;
            virtual bool collideWithTanks(std::list<TankPtr>&, std::list<Bullet>&, float) final;
            virtual bool spawnCollision(std::list<TankPtr>&) final;
            virtual void updateImage() final;
        
        private:
            virtual void draw(sf::RenderTarget& rtWindow, sf::RenderStates rStates) const;
    };
}

#endif