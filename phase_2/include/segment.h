#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

class Segment {
public:
    Point p1, p2;

    Segment(const Point& p1, const Point& p2);

    bool equals(const Segment& seg) const;

    void draw(sf::RenderWindow& window) const;
};

#endif // SEGMENT_H
