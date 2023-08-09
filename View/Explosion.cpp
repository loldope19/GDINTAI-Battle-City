#include "Explosion.h"

using namespace views;      // No idea why this doesn't work--

Explosion::Explosion(Map& cMap, Tank& cTank) {
    if (!cTank.bPlayer)
        cMap.nDestroyedEnemy += 1;
    
    cImg = cMap.cSprite.explosionSprite;
    cImg.scale(cMap.sScreen.nScale, cMap.sScreen.nScale);
    cImg.setPosition(cTank.vecPosition);

    cImg.setTextureRect(sf::IntRect(0, 0, 100, 100));

    cTimer.restart();
    cSound.Sounds["explosion"].play();
}

Explosion::~Explosion() {}

void Explosion::update() {
    if (cTimer.getElapsedTime().asSeconds() >= 0.4) {
        if (nImgNum < 2)
            nImgNum++;
        
        cImg.setTextureRect(sf::IntRect(nImgNum * 100, 0, 100, 100));
        cTimer.restart();
    }
}

bool Explosion::stillExist() {
    if (cSound.Sounds["explosion"].getStatus() == sf::Sound::Status:: Playing) {
        this->update();
        return true;
    }
    else
        return false;
}

void Explosion::draw(sf::RenderTarget& rtWindow, sf::RenderStates) const {
    rtWindow.draw(cImg);
}