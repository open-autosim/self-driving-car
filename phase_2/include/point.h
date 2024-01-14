#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>

class Point {
public:
    float x, y;

    Point(float x, float y);

    bool equals(const Point& point) const;

    void draw(sf::RenderWindow& window) const;
};

#endif // POINT_H
