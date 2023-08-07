#include "Block.h"

using namespace views;

void Block::setImg(GameSprite& cSprite) {
    switch (type) {
        case Block::Type::AIR:
            cImg = cSprite.airSprite;
            break;
        
        case Block::Type::BRICK:
            cImg = cSprite.brickSprite;
            break;

        case Block::Type::STONE:
            cImg = cSprite.stoneSprite;
            break;
        
        case Block::Type::GREEN:
            cImg = cSprite.greenSprite;
            break;
        
        case Block::Type::WATER:
            cImg = cSprite.waterSprite;
            break;
        
        case Block::Type::ENDMAP:
            cImg = cSprite.stoneSprite;
            break;
        
        case Block::Type::EAGLE:
            cImg = cSprite.baseSprite;
            break;
        
        case Block::Type::EAGLE_DEAD:
            cImg = cSprite.baseDedSprite;
            break;
    }
}

void Block::setHardness() {
    switch (type) {
        case Block::Type::BRICK:
            nHardness = Hardness1;
            break;
        
        case Block::Type::STONE:
            nHardness = Hardness3;
            break;
        
        case Block::Type::EAGLE:
            nHardness = Hardness0;
            break;
    }
}

void Block::setMoveMode() {
    switch (type) {
        case Block::Type::AIR:
            move = Move::MOVEABLE;
            break;
        
        case Block::Type::GREEN:
            move = Move::MOVEABLE;
            break;
        
        case Block::Type::WATER:
            move = Move::WATER;
            break;
        
        case Block::Type::ENDMAP:
            move = Move::ENDMAP;
            break;

        default:
            move = Move::NOT_MOVEABLE;
            break;
    }
}

void Block::shotBlock(GameSprite& cSprite) {
    if (nHardness > 0) {
        nHardness--;
    }
    else {
        type = Type::AIR;
        this->setImg(cSprite);
    }
}

void Block::shotEagle(Map& cMap) {
    sf::Vector2f position;

    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            position = cMap.cTab[26 + y][14 + x].cImg.getPosition();
			cMap.cTab[26 + y][14 + x].cImg = cMap.cSprite.baseDedSprite;
			cMap.cTab[26 + y][14 + x].cImg.setTextureRect(sf::IntRect(x * 50, y * 50, 100, 100));
			cMap.cTab[26 + y][14 + x].cImg.setPosition(position);
			cMap.cTab[26 + y][14 + x].cImg.setScale(cMap.sScreen.nScale, cMap.sScreen.nScale);
			cMap.cTab[26 + y][14 + x].move = Block::Move::NOT_MOVEABLE;
			cMap.cTab[26 + y][14 + x].type = Block::Type::EAGLE_DEAD;
			cMap.cTab[26 + y][14 + x].setHardness();
        }
    }
}