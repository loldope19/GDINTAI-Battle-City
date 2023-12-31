#include "../include/Tank.h"
#include "../include/Map.h"

Tank::Tank(const float &x, const float &y, const float &width, const float &height, const sf::String &file, int nObjID)
    : life(true), mX(x), mY(y), mDx(0.f), mDy(0.f), mFile(file), mDir(0), mCollision(false),
    mCurrentFrame(0.f), mSpeed(0.f), mWidth(width), mHeight(height), 
    bullet(x, y) {
    this->nObjID = nObjID;
    mTexture.loadFromFile(mFile);
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(78, 39, mWidth, mHeight));
    mSprite.setPosition(x, y);
}

void Tank::animate(const sf::Int64 &time) {
    mCurrentFrame += 0.005f * time;
    if (mCurrentFrame >= 2)
        mCurrentFrame -= 2;

    if (mDx > 0.f)
        mSprite.setTextureRect(sf::IntRect(0 + 39 * (int)mCurrentFrame, 0, 39, 39));
    if (mDx < 0.f)
        mSprite.setTextureRect(sf::IntRect(78 + 39 * (int)mCurrentFrame, 0, 39, 39));
    if (mDy > 0.0f)
        mSprite.setTextureRect(sf::IntRect(0 + 39 * (int)mCurrentFrame, 39, 39, 39));
    if (mDy < 0.0f)
        mSprite.setTextureRect(sf::IntRect(78 + 39 * (int)mCurrentFrame, 39, 39, 39));
}

void Tank::collapse() {
    life = false;
    bullet.present = false;
    mSprite.setPosition(fInitialX, fInitialY);
}

void Tank::map_interaction(Map &map) {
    for (int i = mY / 24; i < (mY + mHeight) / 24; ++i)
        for (int j = mX / 24; j < (mX + mWidth) / 24; ++j) {
            char tile = map.get_tile(i, j);

            if (tile >= '0' && tile <= '2') {
                if (mDy > 0.f)
                    mY = i * 24 - mHeight;

                if (mDy < 0.f)
                    mY = (float)i * 24 + 24;

                if (mDx > 0.f)
                    mX = j * 24 - mWidth;

                if (mDx < 0.f)
                    mX = (float)j * 24 + 24;
            }
        }

}

void Tank::tank_interaction() {
    if (mDy > 0.f)
        mY -= 0.3f;

    if (mDy < 0.f)
        mY += 0.3f;

    if (mDx > 0.f)
        mX -= 0.3f;

    if (mDx < 0.f)
        mX += 0.3f;
}

void Tank::setPosition(float fX, float fY) {
    mSprite.setPosition(fX, fY);
}