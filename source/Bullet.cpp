#include "../include/Bullet.h"
#include "../include/Map.h"

Bullet::Bullet(const float &x, const float &y)
    : present(false), mX(x), mY(y), mDir(0), mDx(0.f), mDy(0.f), timeBeforeShot(0.f) {

    mTexture.loadFromFile("media/bulletSprite.png");
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 9, 12));
    mSprite.setPosition(x, y);
}

void Bullet::move(const sf::Int64 &time) {
    switch (mDir) {
        case 0:
            mDx = 0.3f;
            mDy = 0;
			mSprite.setRotation(90.f);
            break;

        case 1:
            mDx = -0.3f;
            mDy = 0;
			mSprite.setRotation(-90.f);
            break;

        case 2:
            mDx = 0;
            mDy = 0.3f;
			mSprite.setRotation(180.f);
            break;

        case 3:
            mDx = 0;
            mDy = -0.3f;
			mSprite.setRotation(0.f);
            break;
    }

    mX += mDx * time;
    mY += mDy * time;
	mSprite.setPosition(mX, mY);
}

void Bullet::update(Map &map, const sf::Int64 &time, float &x, const float &y, const int &dir) {
    if (present) {
        move(time);
        map_interaction(map);
    }
    else {
		mDir = dir;
        switch (mDir) {
        case 0:
            mX = x + 35.f;
            mY = y + 15.f;
            break;

        case 1:
            mX = x + 7.f;
            mY = y + 23.f;
            break;

        case 2:
            mX = x + 23.f;
            mY = y + 32.f;
            break;

        case 3:
            mX = x + 15.f;
            mY = y + 5.f;
            break;
        }
		mSprite.setPosition(mX, mY);
    }
}

void Bullet::map_interaction(Map &map) {
    for (int i = mY / 24; i < (mY + 12) / 24; ++i)
        for (int j = mX / 24; j < (mX + 9) / 24; ++j) {
            char tile = map.get_tile(i, j);

            if (tile == '0' || tile == '2')
                present = false;

            if (tile == '1') {
                map.break_wall(i, j);
                present = false;
            }
        }
}
