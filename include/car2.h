#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "controls.h"
#include "sensor.h"
#include <string>
#include <optional>
#include "server.h"
#include <nlohmann/json.hpp>

class Car {
public:

    static int nextID;
    
    Car(float x, float y, float width, float height, float roadLeft, float roadRight, std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders, std::string controlsType, int maxSpeed = 4, int id = nextID);
    ~Car(); 

    int id;
    Sensor *sensor;
    
    sf::Sprite sprite;
    sf::Texture texture; 
    std::vector<sf::Vector2f> polygon;
    
    void update(std::vector<Car> traffic, Server& server);  
    void draw(sf::RenderWindow& window, std::string color);
    void createPolygon();
    void assessDamage(std::vector<Car> traffic);
    void sendData(Server& server);
    void receiveData(Server& server);

    float getX() const { return x; }
    float getY() const { return y; }
    float getAngle() const { return angle; }
    // get is damaged
    bool isDamaged() const { return damaged; }

    void resetGameState(float x, float y, float width, float height, float roadLeft, float roadRight);

private:
    float x, y, width, height;
    float speed, acceleration, maxSpeed, friction, angle;
    float roadLeft, roadRight;
    
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders;
    

    Controls controls;
    std::string controlsType;

    bool damaged;

    sf::RectangleShape shape;
    sf::ConvexShape polygonShape;
    void move();
};

#endif // CAR_H