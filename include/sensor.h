#ifndef SENSOR_H
#define SENSOR_H

#include <SFML/Graphics.hpp>
#include <vector>

class Car;

class Sensor {
public:
    Sensor(Car& car);
    void update(const std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& roadBorders, const std::vector<std::unique_ptr<Car>>& traffic);
    void draw(sf::RenderWindow& window);

    std::vector<sf::Vector2f*> readings;
    //initialize offsets to be all 0
    std::vector<float> offsets;

private:
    Car& m_car;
    int rayCount;
    float rayLength;
    float raySpread;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> rays;
    

    void castRays();
    sf::Vector2f* getReading(const std::pair<sf::Vector2f, sf::Vector2f>& ray, const std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& roadBorders, const std::vector<std::unique_ptr<Car>>& traffic, int rayIndex);
};

#endif // SENSOR_H
