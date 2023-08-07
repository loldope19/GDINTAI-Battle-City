#include "Game.h"

using namespace controllers;

Game::Game(void) : cMap {cSprite, cFPSClock, rwWindow}, cFPSClock {font} {
    std::srand(std::time(nullptr));
    rwWindow.create(sf::VideoMode(1920, 1080), "GDINTAI - Battle City", sf::Style::Titlebar);
    rwWindow.setFramerateLimit(60);
    cMap.setProperties(rwWindow);

    cState = GameState::EXIT;

    if (!cSprite.isGood()) {
        //MessageBox(NULL, _T("Image not found!"), _T("ERROR"), NULL);
        std::cout << "[ERROR] Image not Found!" << std::endl;
		return;
    }
    if (!font.loadFromFile("../View/Font/joystix monospace.ttf")) {     //CHANGE LOCATION LATER
        std::cout << "[ERROR] Font not Found!" << std::endl;
		return;
    }

    cState = GameState::MENU;
}

Game::~Game() {}

void Game::runGame() {
    while (cState != GameState::EXIT) {
        switch (cState)
        {
        case GameState::MENU:
            this->menu();
            break;
        
        case GameState::SINGLEPLAYERGAME:
            this->startUp(0);
            break;
        
        case GameState::TWOPLAYERGAME:
            this->startUp(1);
            break;

        default:
            break;
        }
    }
}

void Game::startUp(bool bGameState) {
        Single sGame {bGameState, font, cMap, cSprite, rwWindow, cFPSClock};
        sGame.runSingle();

        cState = GameState::MENU;
}

void Game::menu() {
    const int n {3};
    sf::Text sText[n];
    sf::String strOptions[] {"1 Player", "2 Player", "Exit"};
    sf::Sprite cMenuStone = cSprite.bigStoneSprite;

    for (int i = 0; i < n; i++) {
        sText[i].setFont(font);
        sText[i].setCharacterSize(rwWindow.getSize().y / 12);
        sText[i].setString(strOptions[i]);
        sText[i].setPosition(float(rwWindow.getSize().y / 3), 
                             float(rwWindow.getSize().y / 2.5 + i * rwWindow.getSize().y / 6.4));
    }

    cSprite.tankSprite.setScale(float(cMap.sScreen.nScale * 1.5), float(cMap.sScreen.nScale * 1.5));

    cIcon = GameState::SINGLEPLAYERGAME;

    while (cState == GameState::MENU) {
        cFPSClock.stopClock();
        this->eventsMenu();

        for (int i = 0; i < n; i++) {
            if (i == int(cIcon) - 1) {
                sText->setFillColor(sf::Color::Red);
                cSprite.tankSprite.setPosition(sText[i].getPosition());
                cSprite.tankSprite.move(float(rwWindow.getSize().x) / -20.0f, 0);
            }
            else
                sText[i].setFillColor(sf::Color::White);
        }

        rwWindow.clear();

        for (int y = 0; y < 15; y++) {
            for (int x = 0; x < cMap.sScreen.nWidthinBlocks / 2; x++) {
                if (x == 0 || y == 0 || x == cMap.sScreen.nWidthinBlocks / 2 - 1 || y == 14) {
                    cMenuStone.setScale(cMap.sScreen.nScale, cMap.sScreen.nScale);
                    cMenuStone.setPosition(float(cMap.sScreen.nSides + x  * (cMap.sScreen.nBlockSize * 2)), float(cMap.sScreen.topBot + y * (cMap.sScreen.nBlockSize * 2)));
                    rwWindow.draw(cMenuStone);
                }
            }   
        }

        cSprite.bgSprite.setPosition(float(std::round(cMap.sScreen.nWidthinBlocks / 8) * cMap.sScreen.nBlockSize + cMap.sScreen.nSides), float(4 * cMap.sScreen.nWidthinBlocks + cMap.sScreen.topBot));
		cSprite.bgSprite.setScale(cMap.sScreen.nScale * 0.8, cMap.sScreen.nScale * 0.8);
		rwWindow.draw(cSprite.bgSprite);

        cSprite.controlSprite.setPosition(1050, 780);
        cSprite.controlSprite.setScale(cMap.sScreen.nScale * 1.2, cMap.sScreen.nScale * 1.2);
        rwWindow.draw(cSprite.controlSprite);
        rwWindow.draw(cSprite.tankSprite);

        for (int i = 0; i < n; i++) {
            rwWindow.draw(sText[i]);
        }
        cFPSClock.draw(rwWindow);
        rwWindow.display();
    }
}

void Game::eventsMenu() {
    sf::Event eEvent;

    while (rwWindow.pollEvent(eEvent)) {
        // Press ESC or the X button in the window
		if (eEvent.type == sf::Event::Closed || 
            eEvent.type == sf::Event::KeyPressed &&
			eEvent.key.code == sf::Keyboard::Escape)
			cState = GameState::EXIT;
		// 1 player mode (tank in the right position + enter)
		else if (eEvent.type == sf::Event::KeyPressed && 
                eEvent.key.code == sf::Keyboard::Key::Return &&
			    cIcon == GameState::SINGLEPLAYERGAME) {
			cState = cIcon;
		}
		// 2 players mode (tank in the right position + enter)
		else if (eEvent.type == sf::Event::KeyPressed && 
                eEvent.key.code == sf::Keyboard::Key::Return &&
			    cIcon == GameState::TWOPLAYERGAME){
			cState = cIcon;
		}
		// EXIT mode (tank in the right position + enter)
		else if (eEvent.type == sf::Event::KeyPressed &&
                eEvent.key.code == sf::Keyboard::Key::Return &&
			    cIcon == GameState::EXIT){
			cState = cIcon;
		}
		// moving the tank icon - arrow up
		else if (eEvent.type == sf::Event::KeyPressed &&
                 eEvent.key.code == sf::Keyboard::Key::Up && 
                 int(cIcon) > 1){
			switch (cIcon){
			case GameState::TWOPLAYERGAME: cIcon = GameState::SINGLEPLAYERGAME;
				break;
			case GameState::EXIT: cIcon = GameState::TWOPLAYERGAME;
				break;
			}
		}
		// moving the tank icon - arrow down
		else if (eEvent.type == sf::Event::KeyPressed &&
                 eEvent.key.code == sf::Keyboard::Key::Down &&
                 int(cIcon) < 3){
			switch (cIcon){
                case GameState::SINGLEPLAYERGAME: 
                    cIcon = GameState::TWOPLAYERGAME;
                    break;
                case GameState::TWOPLAYERGAME: 
                    cIcon = GameState::EXIT;
                    break;
			}
		}
		else if (eEvent.type == sf::Event::KeyPressed && 
                 eEvent.key.code == sf::Keyboard::T){
			cFPSClock.toggleClock();
		}
    }
}