#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>

class Point {
public:
    float x, y;

    Point(float x, float y);

    bool equals(const Point& point) const;

    // Add default values for size and color here
    void draw(sf::RenderWindow& window, float size = 18, sf::Color color = sf::Color::Black) const;
};

#endif // POINT_H
