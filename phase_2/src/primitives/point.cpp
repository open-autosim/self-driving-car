#include "primitives/point.h" // Ensure the include path is correct

Point::Point(float x, float y) : x(x), y(y) {}

bool Point::equals(const Point& point) const {
    return x == point.x && y == point.y;
}

// Update the draw method to use size and color parameters
void Point::draw(sf::RenderWindow& window, float size, sf::Color color) const {
    sf::CircleShape circle(size / 2); // radius = half of size
    circle.setFillColor(color);
    circle.setPosition(x - size / 2, y - size / 2); // adjust position to center
    window.draw(circle);
}

