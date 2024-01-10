#ifndef SENSOR_H
#define SENSOR_H

#include <SFML/Graphics.hpp>
#include <vector>

class Car;

class Sensor {
public:
    Sensor(Car& car);
    void update(const std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& borders, std::vector<Car> traffic);
    void draw(sf::RenderWindow& window);

private:
    Car& m_car;
    int rayCount;
    float rayLength;
    float raySpread;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> rays;
    std::vector<sf::Vector2f*> readings;

    void castRays();
    sf::Vector2f* getReading(const std::pair<sf::Vector2f, sf::Vector2f>& ray, const std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& roadBorders, std::vector<Car> traffic);
};

#endif // SENSOR_H
