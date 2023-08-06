#ifndef VIEW_SPRITE_H
#define VIEW_SPRITE_H

namespace views {
    class Sprite {
        public:
            // Block Textures
            sf::Texture airTexture;
            sf::Texture brickTexture;
            sf::Texture stoneTexture;
            sf::Texture bigStoneTexture;
            sf::Texture greenTexture;
            sf::Texture waterTexture;

            // Menu Textures
            sf::Texture backgroundTex;
            sf::Texture controlTex;

            // Tank Textures
            sf::Texture greenTankTex;
            sf::Texture yellowTankTex;
            sf::Texture redTankTex;
            sf::Texture greyTankTex;

            // Bullet Texture
            sf::Texture bulletTexture;

            // Base (Eagle) Texture
            sf::Texture baseTexture;
            sf::Texture baseDedTexture;

            // megumin
            sf::Texture explosionTex;

        public:
            // Block Sprites
            sf::Sprite airSprite;
            sf::Sprite brickSprite;
            sf::Sprite stoneSprite;
            sf::Sprite bigStoneSprite;
            sf::Sprite greenSprite;
            sf::Sprite waterSprite;

            // Menu Sprites
            sf::Sprite tankSprite;
            sf::Sprite bgSprite;
            sf::Sprite controlSprite;

            // Tank Sprites
            sf::Sprite greenTankSprite;
            sf::Sprite yellowTankSprite;
            sf::Sprite redTankSprite;
            sf::Sprite greyTankSprite;

            // Bullet Sprite
            sf::Sprite bulletSprite;

            // Base (Eagle) Sprite
            sf::Sprite baseSprite;
            sf::Sprite baseDedSprite;

            // megumin sprite
            sf::Sprite explosionSprite;

            bool bLoaded;

        public:
            Sprite(void);
            bool isGood();

            void loadTextures();
            void loadSprites();
    };
}

#endif