#ifndef SEGMENT_H
#define SEGMENT_H

#include "primitives/point.h"
#include <memory>

class Segment {
public:
    std::shared_ptr<Point> p1;
    std::shared_ptr<Point> p2;

    Segment(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2);

    bool equals(const Segment& seg) const;
    bool includes(const Point& point) const;
    void draw(sf::RenderWindow& window, float width = 2, sf::Color color = sf::Color::Black, bool dash = false) const;
};

#endif // SEGMENT_H
