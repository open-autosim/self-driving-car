#include "point.h"

Point::Point(float x, float y) : x(x), y(y) {}

bool Point::equals(const Point& point) const {
    return x == point.x && y == point.y;
}

void Point::draw(sf::RenderWindow& window) const {
    sf::CircleShape circle(9); // radius = half of size
    circle.setFillColor(sf::Color::Black);
    circle.setPosition(x - 9, y - 9); // adjust position to center
    window.draw(circle);
}
