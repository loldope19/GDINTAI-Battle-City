#ifndef MODEL_ENEMY_H
#define MODEL_ENEMY_H

#include "Tank.h"
#include "Map.h"

namespace models {
    class Enemy : public Tank {
        public:
            enum class MoveState {
                DOWN, LEFT, RIGHT, UP
            };
        
        public:
            Enemy(std::list<Explosion>& Explosions, std::list<Bullet>& Bullets, GameSprite& cSprite, Map& cMap, int objID, Level::newTankPos tankPos, bool bIsPlayer, Move CMove);
            virtual ~Enemy();

        public:
            void checkMove();
    };
}

#endif