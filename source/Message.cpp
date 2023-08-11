//#include <SFML/System/String.hpp>
#include "../include/Message.h"

Message::Message(const float &x, const float &y, const sf::String &str)
    : mX(x), mY(y) {
    
    mFont.loadFromFile("media/PressStart2P.ttf");
    mStr.setFont(mFont);
    mStr.setString(str);
    mStr.setPosition(mX, mY);
    mStr.setCharacterSize(25);
}

void Message::setString(const sf::String &str) {
    mStr.setString(str);
}