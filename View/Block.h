#ifndef VIEW_BLOCK_H
#define VIEW_BLOCK_H

#include "SFML/Graphics.hpp"

#include "../Model/Map.h"
#include "Sprite.h"
#include "../Macro.h"

const int Hardness0 = 0;
const int Hardness1 = 1;
const int Hardness3 = 3;

class Map;

namespace views {
    class Block {
        private:
            int nHardness = Hardness0;
            sf::Sprite cImg;

        public:
            bool bHide = false;
            enum class Type {
                AIR, BRICK, STONE, GREEN, WATER, ENDMAP, EAGLE, EAGLE_DEAD
            } type;

            enum class Move {
                MOVEABLE, NOT_MOVEABLE, WATER, ENDMAP
            } move;

            enum class Pos {
                POS1, POS2, POS3, POS4
            } pos;

            void setImg(Sprite& cSprite);
            void setHardness();
            void setMoveMode();
            void shotBlock(Sprite& cSprite);
            void shotEagle(Map& cMap);
    };
}

#endif