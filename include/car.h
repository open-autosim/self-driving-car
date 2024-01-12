#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory> // For std::unique_ptr
#include "sensor.h" // Assuming Sensor is a class you have
#include "server.h" // Assuming Server is a class you have
#include "controls.h" // Assuming Controls is a class you have
#include <string>
#include <optional>
#include <nlohmann/json.hpp>

class Car {
public:
    Car(float x, float y, float width, float height, float roadLeft, float roadRight, 
        std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders, std::string controlsType, 
        int maxSpeed = 10, int id = nextID);
    ~Car();

    void update(const std::vector<Car>& traffic, Server& server);
    void draw(sf::RenderWindow& window, const std::string& color);
    void resetGameState(float x, float y, float width, float height, float roadLeft, float roadRight);

    float getX() const { return x; }
    float getY() const { return y; }
    float getAngle() const { return angle; }

    std::vector<sf::Vector2f> polygon;
    int id;

private:
    void move();
    void createPolygon();
    void assessDamage(const std::vector<Car>& traffic);
    void sendData(Server& server);
    void receiveData(Server& server);

    float x, y;
    float width, height;
    float speed;
    float acceleration;
    float maxSpeed;
    float friction;
    float angle;
    float roadLeft, roadRight;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders;
    // std::vector<sf::Vector2f> polygon;
    sf::ConvexShape polygonShape;
    Controls controls;
    std::string controlsType;
    std::unique_ptr<Sensor> sensor;
    bool damaged = false;
    static int nextID;

    // Precomputed values for polygon creation
    float rad;
    float alpha;
};

#endif // CAR_H
