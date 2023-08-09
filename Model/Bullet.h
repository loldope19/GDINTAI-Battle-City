#ifndef MODEL_BULLET_H
#define MODEL_BULLET_H

#include "SFML/Graphics.hpp"
#include "../Macro.h"
#include "../Controller/Collisionable.h"

#include "Map.h"
#include "../View/Sound.h"
#include "../View/Sprite.h"

namespace models {
    class Map;

    class Bullet : public sf::Drawable, public Collisionable {
        public:
            Bullet(GameSprite& cSprite, Map& cMap, sf::Vector2f vecPosition, int objID, Move cMove, bool bIsPlayer);
            ~Bullet();

        public:
            void setStartPos(sf::Vector2f vecPosition);
            virtual bool collision(Pos PosMap, sf::FloatRect& sRect) final;
            virtual bool collideWithTanks(std::list<TankPtr>&, std::list<Bullet>&, float) final;
            virtual void checkCollision(std::list<TankPtr>&, std::list<Bullet>&) override;

            virtual void updateImage();

            bool collideWithBullets(std::list<Bullet>&, sf::FloatRect&);

        private:
            virtual void draw(sf::RenderTarget& rtWindow, sf::RenderStates rsStates) const;
        
    };
}

#endif