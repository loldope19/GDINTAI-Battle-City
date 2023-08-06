#ifndef MODEL_MAP_H
#define MODEL_MAP_H

#include "Clock.h"
//#include "Macro.h"

#include "../View/Sprite.h"
#include "../View/Block.h"
//#include "Tank.h"
//#include "Bullet.h"
//#include "Explosion.h"

//#include "Player1.h"
//#include "Player2.h"
//#include "Enemy.h"
//#include "Sound.h"

const int nBlockSize = 30;

typedef std::array <Block, nBlockSize> Blocks;
typedef std::array <Blocks, nBlockSize> BlockTab;

struct Window {
    int topBot;             // Top & Bottom Screen Space
    int nSides;             // Left & Right Screen Space
    int nBlockSize;         // Block size after Reduction
    int nSideMenu;          // Side Panel/Menu Width
    int nScale;             // Scale of block relative to base dimension
    int nWidthinBlocks;     // Width of Map in blocks
};

struct Level {
    enum class newTankPos {
        LEFT,
        MID,
        RIGHT
    };

    std::list<TankPtr> Tanks;
    std::list<Bullet> Bullets;
    std::list<Explosion> Explosions;

    int nLevelCount;
    int nActualLevel = 0;
    int nTanksID = 2;
    int nEnemyTanks;
    int nPlayerTanks = 3;
    int nEnemyDestroyed = 0;

    sf::Clock timerPlayer1;
    sf::Clock timerPlayer2;
    sf::Clock timerEnemy;

    Level(int nLevelCount = 1) : nLevelCount(nLevelCount) {}
};

namespace models {
    class Map : public sf::Drawable {
        private:
            GameState cState;
            sf::Font font;
	        sf::Text sText1, sText2, enemyStr, livesStr, sLevel;
	        bool bSecRoundPlus = false;
	        int nAliveEnemyTank;
	        sf::Sprite sPlayerTank;
	        sf::Sprite sEnemyTank; 

        public:
            Window sScreen;
            BlockTab cTab;
            Sprite& cSprite;
            Timer& cGameClock;
            sf::RenderWindow& rwWindow;
            Level sLevel;
            int nDestroyedEnemy = 0;

            enum class Set {
                LEFT,
                UP,
                RIGHT,
                DOWN,
                CORNER1,
                CORNER2,
                CORNER3,
                CORNER4,
                CORNERBIG1,
                CORNERBIG2,
                CORNERBIG3,
                CORNERBIG4,
                FULL
            };

            enum class GameState {
                GAME,
                NEXT_LEVEL,
                GAME_OVER,
                EXIT
            };

        public:
            Map(Sprite& pSprite, Timer& cFPSClock, sf::RenderWindow& rwWindow);
            ~Map();

        public: 
            void setProperties(sf::RenderWindow& rwWindow);
            void setSpriteProperties();
            void setInformationProperties();

            int loadMap();

            void addEnemyTank();
            void addPlayer1Tank();
            void addPlayer2Tank();

            void events(Timer&);
            bool gameGood();
            bool checkGameStatus();
            void initiateGame();
            void endGame();
            void setEagle();
            bool checkEagleAlive();
            void nextLevel();
            void gameOver();
            void win();
            void exit();

        private:
            virtual void draw(sf::RenderTarget& rtWindow, sf::RenderStates) const;

        
    };
}

#endif