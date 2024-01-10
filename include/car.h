#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "controls.h"
#include "sensor.h"

class Car {
public:
    Car(float x, float y, float width, float height, float roadLeft, float roadRight, std::vector<sf::Vector2f> borders);
    sf::Sprite sprite;
    sf::Texture texture; 
    void update();  
    void draw(sf::RenderWindow& window);
    // void createPolygon();
    // void assessDamage();

    float getX() const { return x; }
    float getY() const { return y; }
    float getAngle() const { return angle; }

private:
    float x, y, width, height;
    float speed, acceleration, maxSpeed, friction, angle;
    float roadLeft, roadRight;
    
    std::vector<sf::Vector2f> borders;
    std::vector<sf::Vector2f> polygon;

    Controls controls;
    Sensor sensor;

    bool crashed;

    sf::RectangleShape shape;
    sf::ConvexShape polygonShape;
    void move();
};

#endif // CAR_H
