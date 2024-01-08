#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "controls.h"

class Car {
public:
    Car(float x, float y, float width, float height);
    void update(const sf::RenderWindow& window);  // Change to sf::RenderWindow
    void draw(sf::RenderWindow& window);

private:
    float x, y, width, height;
    float speed, acceleration, maxSpeed, friction, angle;
    Controls controls;

    sf::RectangleShape shape;
    void move();
};

#endif // CAR_H
