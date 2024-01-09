#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "controls.h"

class Car {
public:
    Car(float x, float y, float width, float height);
    sf::Sprite sprite;
    sf::Texture texture; 
    void update();  
    void draw(sf::RenderWindow& window);

private:
    float x, y, width, height;
    float speed, acceleration, maxSpeed, friction, angle;
    Controls controls;

    sf::RectangleShape shape;
    void move();
};

#endif // CAR_H
