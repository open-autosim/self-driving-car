#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "controls.h"
#include "sensor.h"
#include <string>
#include <optional>

class Car {
public:
    Car(float x, float y, float width, float height, float roadLeft, float roadRight, std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders, std::string controlsType, int maxSpeed = 4);
    ~Car(); 

    Sensor *sensor;
    
    sf::Sprite sprite;
    sf::Texture texture; 
    std::vector<sf::Vector2f> polygon;
    
    void update(std::vector<Car> traffic);  
    void draw(sf::RenderWindow& window, std::string color);
    void createPolygon();
    void assessDamage(std::vector<Car> traffic);

    float getX() const { return x; }
    float getY() const { return y; }
    float getAngle() const { return angle; }

private:
    float x, y, width, height;
    float speed, acceleration, maxSpeed, friction, angle;
    float roadLeft, roadRight;
    
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders;
    

    Controls controls;

    bool damaged;

    sf::RectangleShape shape;
    sf::ConvexShape polygonShape;
    void move();
};

#endif // CAR_H
