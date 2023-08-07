#include "Sound.h"

using namespace views;

Sound::Sound() {
    int i = 0;

    buffer[i].loadFromFile("SFX/move.wav");
    Sounds["move"].setBuffer(buffer[i]);
    Sounds["move"].setLoop(true);
    Sounds["move"].setVolume(50);
    i++;

    buffer[i].loadFromFile("SFX/tank.wav");
    Sounds["tank"].setBuffer(buffer[i]);
    Sounds["tank"].setLoop(true);
    Sounds["tank"].setVolume(50);
    i++;

    buffer[i].loadFromFile("SFX/gameOver.wav");
    Sounds["gameOver"].setBuffer(buffer[i]);
    Sounds["gameOver"].setLoop(true);
    Sounds["gameOver"].setVolume(50);
    i++;

    buffer[i].loadFromFile("SFX/winning.wav");
    Sounds["winning"].setBuffer(buffer[i]);
    Sounds["winning"].setVolume(75);
    i++;

    buffer[i].loadFromFile("SFX/shot.wav");
    Sounds["shot"].setBuffer(buffer[i]);
    Sounds["shot"].setVolume(75);
    i++;

    buffer[i].loadFromFile("SFX/block.wav");
    Sounds["block"].setBuffer(buffer[i]);
    Sounds["block"].setVolume(75);
    i++;

    buffer[i].loadFromFile("SFX/explosion.wav");
    Sounds["explosion"].setBuffer(buffer[i]);
    Sounds["explosion"].setVolume(75);
    i++;
}

Sound::~Sound() {}

void Sound::updateSound(std::list<TankPtr>& tanks) {
    bool bIsMoving = false;

    for (auto& tank : tanks) {
        if (tank->move != Tank::Move::NONE) {
            bIsMoving = true;
            break;
        }
    }

    if (bIsMoving) {
        if (Sounds["move"].getStatus() != sf::Sound::Status::Playing) {
            Sounds["tank"].stop();
				Sounds["move"].play();
        }
    }
    else{
		if (Sounds["tank"].getStatus() != sf::Sound::Status::Playing){
			Sounds["move"].stop();
			Sounds["tank"].play();
		}
	}
}

void Sound::stopAll() {
    Sounds["move"].stop();
	Sounds["tank"].stop();
	Sounds["gameOver"].stop();
	Sounds["winning"].stop();
	Sounds["shot"].stop();
	Sounds["block"].stop();
    Sounds["explosion"].stop();
}