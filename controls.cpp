#include "controls.h"

Controls::Controls() : forward(false), left(false), right(false), reverse(false) {}

void Controls::update(const sf::RenderWindow& window) {
    forward = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    reverse = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}
