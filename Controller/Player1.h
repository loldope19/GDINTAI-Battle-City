#ifndef CONTROLLERS_PLAYER_1_H
#define CONTROLLERS_PLAYER_1_H

#include "../Model/Tank.h"
#include "../Model/Map.h"
#include "../View/Explosion.h"

namespace controllers {
    using namespace views;
    class Player1 : public Tank {
        public:
            Player1(std::list<Explosion>& Explosions, std::list<Bullet>& Bullets, GameSprite& cSprite, Map& cMap, bool bIsPlayer, int objID, Move cMove);
            virtual ~Player1(void);

        public:
            void checkMove();
            void initialPlace();
    };
}

#endif