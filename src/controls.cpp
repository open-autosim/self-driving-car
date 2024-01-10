#include "controls.h"
#include <iostream>

Controls::Controls(std::string controlsType) : forward(false), left(false), right(false), reverse(false), 
controlsType(controlsType) {}

void Controls::update() {

     if (controlsType == "KEYS") {
        forward = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        reverse = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    } else if (controlsType == "DUMMY") {
        // Dummy controls (e.g., do nothing or default behavior)
        forward = true;
        reverse = false;
        left = false;
        right = false;
    } else if (controlsType == "AI") {
        // AI controls (you'll need to implement the logic based on your AI's decision making)
   
    }   
       
}


