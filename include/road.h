#ifndef ROAD_H
#define ROAD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Road {
public:
    Road(float x, float width, int laneCount = 3);

    float getLaneCenter(int laneIndex);
    void draw(sf::RenderWindow& window);
    float getLeft() { return left; }
    float getRight() { return right; }

private:
    float x, width;
    int laneCount;
    float left, right;
    std::vector<sf::Vector2f> borders;

    float lerp(float a, float b, float t);
};

#endif // ROAD_H
