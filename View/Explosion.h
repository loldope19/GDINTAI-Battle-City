#ifndef VIEW_EXPLOSION_H
#define VIEW_EXPLOSION_H

#include "../Model/Map.h"
#include "../Model/Tank.h"
#include "../Macro.h"
#include "Sound.h"
#include "SFML/Graphics.hpp"

namespace views {
    extern Sound sound;

    class Explosion : public sf::Drawable {
        private:
            int nImgNum = 0;
            sf::Clock cTimer;
            sf::Sprite cImg;

        public:
            Explosion(Map& cMap, Tank& cTank);
            ~Explosion();
        
            bool stillExist();
        
        private:
            virtual void draw(sf::RenderTarget& rtWindow, sf::RenderStates) const;
            void update();

    };
}

#endif