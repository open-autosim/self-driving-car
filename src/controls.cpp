#include "controls.h"
#include <iostream>

Controls::Controls() : forward(false), left(false), right(false), reverse(false) {}

void Controls::update() {

    forward = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    reverse = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);    
       
}


