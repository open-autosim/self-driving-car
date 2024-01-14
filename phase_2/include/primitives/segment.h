#ifndef SEGMENT_H
#define SEGMENT_H

#include "primitives/point.h"

class Segment {
public:
    Point p1, p2;

    Segment(const Point& p1, const Point& p2);

    bool equals(const Segment& seg) const;
    bool includes(const Point& point) const;
    void draw(sf::RenderWindow& window, float width = 2, sf::Color color = sf::Color::Black) const;
};

#endif // SEGMENT_H
