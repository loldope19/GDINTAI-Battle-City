#include "Sprite.h"

using namespace views;

GameSprite::GameSprite() {
    bLoaded = false;
    this->loadTextures();
    bLoaded = true;
    this->loadSprites();
}

GameSprite::~GameSprite() {}

bool GameSprite::isGood() {
    return this->bLoaded;
}

void GameSprite::loadTextures() {
    airTexture.loadFromFile("Image/Blocks/airTx.png");
    brickTexture.loadFromFile("Image/Blocks/brickTx.gif");
    stoneTexture.loadFromFile("Image/Blocks/stoneTx.gif");
    bigStoneTexture.loadFromFile("Image/Blocks/stoneBigTx.gif");
    greenTexture.loadFromFile("Image/Blocks/greenTx.png");
    waterTexture.loadFromFile("Image/Blocks/waterTx.gif");

    backgroundTex.loadFromFile("Image/battle-city_title.png");
    controlTex.loadFromFile("Image/control.png");

    greenTankTex.loadFromFile("Image/Tanks/tankGreenTx.png");
    yellowTankTex.loadFromFile("Image/Tanks/tankYellowTx.png");
    redTankTex.loadFromFile("Image/Tanks/tankRedTx.png");
    greyTankTex.loadFromFile("Image/Tanks/tankGreyTx.png");

    bulletTexture.loadFromFile("Image/bulletTx.png");

    baseTexture.loadFromFile("Image/Bird/birdTx.png");
    baseDedTexture.loadFromFile("Image/Bird/birdDeadTx.png");

    explosionTex.loadFromFile("Image/explosionTx.gif");
}

void GameSprite::loadSprites() {
    airSprite.setTexture(airTexture);
    brickSprite.setTexture(brickTexture);
    stoneSprite.setTexture(stoneTexture);
    bigStoneSprite.setTexture(bigStoneTexture);
    greenSprite.setTexture(greenTexture);
    waterSprite.setTexture(waterTexture);

    bgSprite.setTexture(backgroundTex);
    controlSprite.setTexture(controlTex);
    tankSprite.setTexture(yellowTankTex);
    tankSprite.setTextureRect(sf::IntRect(200, 0, 100, 100));
    tankSprite.rotate(90);

    greenTankSprite.setTexture(greenTankTex);
    yellowTankSprite.setTexture(yellowTankTex);
    redTankSprite.setTexture(redTankTex);
    greyTankSprite.setTexture(greyTankTex);

    bulletSprite.setTexture(bulletTexture);

    baseSprite.setTexture(baseTexture);
    baseDedSprite.setTexture(baseDedTexture);

    explosionSprite.setTexture(explosionTex);
}