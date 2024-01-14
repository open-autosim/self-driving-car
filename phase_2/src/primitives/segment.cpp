#include "primitives/segment.h"

Segment::Segment(const Point& p1, const Point& p2) : p1(p1), p2(p2) {}

bool Segment::equals(const Segment& seg) const {
    return includes(seg.p1) && includes(seg.p2);
}

bool Segment::includes(const Point& point) const {
    return (p1.equals(point) || p2.equals(point));
}


void Segment::draw(sf::RenderWindow& window, float width, sf::Color color) const {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(p1.x, p1.y);
    line[1].position = sf::Vector2f(p2.x, p2.y);
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;
    window.draw(line);
}

// void Segment::draw(sf::RenderWindow& window, float width, sf::Color color) const {
//     sf::Vector2f direction(p2.x - p1.x, p2.y - p1.y);
//     float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

//     sf::RectangleShape line(sf::Vector2f(length, width));
//     line.setPosition(p1.x, p1.y);
//     line.setFillColor(color);

//     // Calculate the angle to rotate the line
//     float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;
//     line.setRotation(angle);

//     window.draw(line);
// }