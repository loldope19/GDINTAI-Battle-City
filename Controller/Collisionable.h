#ifndef CONTROLLER_COLLISIONABLE_H
#define CONTROLLER_COLLISIONABLE_H

#include <SFML\Graphics.hpp>
#include <list>
#include <memory>

#include "../Macro.h"
#include "../View/Sprite.h"
#include "../Model/Map.h"
#include "../Model/Tank.h"

const float PlayerSpeed = 0.033f;
const float EnemySpeed = 0.04f;
const float BulletSpeed = 0.015f;

namespace controllers {
    using namespace models;
    typedef std::unique_ptr<Tank> TankPtr;

    class Collisionable {
        public:
            GameSprite& cSprite;        // Stores Sprites
            Map& cMap;              // Stores Map

            enum class Move : int {LEFT, RIGHT, UP, DOWN, NONE};
            struct Pos {
                int x;
                int y;
            } posMap;

            sf::Clock cTimer;               // Limiting Timer
            float fSpeed;                   // Object's Rate of Shift

            sf::Vector2f vecPosition;       // Object Position
            sf::Sprite sSprite;             // Object Image
            Move cMove;                     // Current Image Status (in a sense)
            Move cLastMove;                 // Previous Move
            const int objID;

            bool bExists;
            const bool bPlayer;

        public:
            Collisionable(GameSprite& cSprite, Map& cMap, bool bPlayer, int ID, Move cMove);
            virtual ~Collisionable(void);
        
        public:
            // Updates image relative to the return of the object
            virtual void updateImage() = 0;
            // Checks collisions with blocks and starting collisions with tanks
            virtual void checkCollision(std::list<TankPtr>&, std::list<Bullet>&);
            // Checks for collisions with the selected block determined on the basis of the + position passed to the box
            virtual bool collision(Pos, sf::FloatRect&) = 0;
            // Checks collisions with tanks and the player
            virtual bool collideWithTanks(std::list<TankPtr> &, std::list<Bullet> &, float) = 0;
    };
}

#endif