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
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getBorders() { return borders; }
    int getLaneCount() { return laneCount; }

private:
    float center, width;
    int laneCount;
    float left, right;
    float margin = 7.0f; // Margin between the road edge and the border line
    
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders;
};

#endif // ROAD_H
