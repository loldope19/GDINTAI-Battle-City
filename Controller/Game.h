#ifndef CONTROLLER_GAME_H
#define CONTROLLER_GAME_H

#include "../Model/Clock.h"
#include "../Model/Map.h"
//#include "Single.h"
#include "../View/Sprite.h"
#include "../View/Block.h"

#define NOMINMAX

enum class GameState {
    MENU,
    SINGLEPLAYERGAME,
    TWOPLAYERGAME,
    EXIT
};

namespace controllers {
    class Game {
        private:
            sf::RenderWindow rwWindow;
            GameState cIcon;
            GameState cState;

            GameSprite cSprite;
            Map cMap;

            sf::Font font;
            Timer cFPSClock;

        public:
            Game(void);
            ~Game();

        public:
            void runGame();

        private:
            void menu();
            void eventsMenu();
            void startUp(bool bGameState);


    };
}


#endif