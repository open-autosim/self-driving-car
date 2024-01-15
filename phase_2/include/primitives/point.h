#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>

class Point {
public:
    float x, y;

    Point(float x, float y);

    // Updated equals method to take const reference
    bool equals(const Point& other) const;

    // Add default values for size and color here
    void draw(sf::RenderWindow& window, float size = 18, sf::Color color = sf::Color::Black, bool outline = false, bool fill = false) const;
};

#endif // POINT_H
