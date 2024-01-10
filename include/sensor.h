#ifndef SENSOR_H
#define SENSOR_H

#include <SFML/Graphics.hpp>
#include <vector>

class Car;

class Sensor {
public:
    Sensor(Car& car);
    void update(const std::vector<sf::Vector2f>& borders);
    void draw(sf::RenderWindow& window);
    void drawThickLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, sf::Color color, float thickness);

private:
    Car& m_car;
    int rayCount;
    float rayLength;
    float raySpread;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> rays;
    std::vector<sf::Vector2f*> readings;

    void castRays();
    sf::Vector2f* getReading(const std::pair<sf::Vector2f, sf::Vector2f>& ray, const std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& roadBorders);
};

#endif // SENSOR_H
