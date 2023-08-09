#ifndef CONTROLLERS_PLAYER_2_H
#define CONTROLLERS_PLAYER_2_H

#include "../Model/Tank.h"
#include "../Model/Map.h"

namespace controllers {
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