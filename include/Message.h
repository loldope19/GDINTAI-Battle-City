#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Message {
private:
    float mX, mY;

    sf::Font mFont;
    sf::Text mStr;

public:
    explicit Message(const float &x, const float &y, const sf::String &str);

    void print(sf::RenderWindow &window) { window.draw(mStr); }
};
