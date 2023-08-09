#ifndef MODEL_SINGLE_H
#define MODEL_SINGLE_H

#include "../View/Sprite.h"
#include "../View/Sound.h"
#include "Map.h"
#include "Clock.h"

namespace models {
    extern Sound cSound;

    class Single {
        private:
            bool bGameType;
            sf::Font& cFont;
            Map& cMap;
            GameSprite& cSprite;
            sf::RenderWindow& rwWindow;
            Timer& cFPSClock;
        
        public:
            Single(bool bGameType, sf::Font& font, Map& cMap, GameSprite& cSprite, sf::RenderWindow& rwWindow, Timer& cFPSClock);
            ~Single();
        
        public:
            void runSingle();

        private:
            void clearDeadObjects();

    };
}

#endif