#include "primitives/point.h" // Ensure the include path is correct

Point::Point(float x, float y) : x(x), y(y) {}

// Updated equals method implementation
bool Point::equals(const Point& other) const {
    return x == other.x && y == other.y;
}

void Point::draw(sf::RenderWindow& window, float size, sf::Color color, bool outline, bool fill) const {
    // First, draw the filled circle
    sf::CircleShape filledCircle(size / 2); // radius = half of size
    filledCircle.setFillColor(color);
    filledCircle.setPosition(x - size / 2, y - size / 2); // adjust position to center
    window.draw(filledCircle);

    // Then, if outline is true, draw the outline circle
    if (outline) {
        float outlineSize = size * 0.6f;
        sf::CircleShape outlineCircle(outlineSize / 2);
        outlineCircle.setFillColor(sf::Color::Transparent); // Make fill color transparent
        outlineCircle.setOutlineColor(sf::Color::Yellow);   // Set outline color
        outlineCircle.setOutlineThickness(1.2);               // Set outline thickness
        outlineCircle.setPosition(x - outlineSize / 2, y - outlineSize / 2); // Same position as the filled circle
        window.draw(outlineCircle);
    }

    if (fill) {
        float fillSize = size * 0.4f;
        sf::CircleShape fillCircle(fillSize / 2);
        fillCircle.setFillColor(sf::Color::Yellow);
        fillCircle.setPosition(x - fillSize / 2, y - fillSize / 2);
        window.draw(fillCircle);
    }
}
