#include "segment.h"

Segment::Segment(const Point& p1, const Point& p2) : p1(p1), p2(p2) {}

bool Segment::equals(const Segment& seg) const {
    return (p1.equals(seg.p1) && p2.equals(seg.p2)) || (p1.equals(seg.p2) && p2.equals(seg.p1));
}

void Segment::draw(sf::RenderWindow& window) const {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(p1.x, p1.y);
    line[1].position = sf::Vector2f(p2.x, p2.y);
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;
    window.draw(line);
}
