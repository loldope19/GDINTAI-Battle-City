#include "Block.h"

using namespace views;

void Block::setImg(Sprite& cSprite) {
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

void Block::shotBlock(Sprite& cSprite) {
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
            position = cMap.tab[26 + y][14 + x].cImg.getPosition();
			cMap.tab[26 + y][14 + x].cImg = cMap.spr.EagleDead;
			cMap.tab[26 + y][14 + x].cImg.setTextureRect(sf::IntRect(x * 50, y * 50, 100, 100));
			cMap.tab[26 + y][14 + x].cImg.setPosition(position);
			cMap.tab[26 + y][14 + x].cImg.setScale(cMap.pr.scale, cMap.pr.scale);
			cMap.tab[26 + y][14 + x].move = Block::Move::NOT_MOVEABLE;
			cMap.tab[26 + y][14 + x].type = Block::Type::EAGLE_DEAD;
			cMap.tab[26 + y][14 + x].setHardness();
        }
    }
}