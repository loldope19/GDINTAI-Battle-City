#include "Clock.h"

using namespace models;

Timer::Timer(sf::Font& font) : font(font), nActualFPS(), nFPSCount() {
    sTime.restart();
}

Timer::~Timer() {}

void Timer::toggleClock() {
    bClockOn = !bClockOn;
}

void Timer::restart() {
    sTime.restart();
}

void Timer::stopClock() {
    if (bClockOn)
        this->toggleClock();
}

void Timer::draw(sf::RenderWindow& rwWindow) {
    if (bClockOn) {
        nFPSCount = sTime.getElapsedTime().asSeconds();

        sText.setFont(font);
        sText.setCharacterSize(rwWindow.getSize().y / 24);
        sText.setFillColor(sf::Color::Red);
        sText.setString("Clock: " + std::to_string(nFPSCount));
        sText.setPosition(float(rwWindow.getSize().x - sText.getGlobalBounds().width), 0.0f);

        rwWindow.draw(sText);
    }
}