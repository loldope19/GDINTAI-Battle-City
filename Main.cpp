#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <list>
#include <map>
#include <memory>
#include <unordered_map>
#include <windows.h>
#include <tchar.h>
#include <math.h>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "Controller/Collisionable.cpp"
#include "Controller/Game.cpp"
/*
#include "Model/Bullet.cpp"
#include "Model/Clock.cpp"
#include "Model/Enemy.cpp"
#include "Model/Map.cpp"
#include "Model/Single.cpp"
#include "Model/Tank.cpp"

#include "View/Block.cpp"
#include "View/Explosion.cpp"
#include "View/Sound.cpp"
#include "View/Sprite.cpp"
*/
Sound cSound;

int main() {
   Game CGame;
   CGame.runGame();

   return 0;
}
