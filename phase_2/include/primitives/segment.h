#ifndef SEGMENT_H
#define SEGMENT_H

#include "primitives/point.h"
#include <memory>
#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

class Segment {
public:
    std::shared_ptr<Point> p1;
    std::shared_ptr<Point> p2;

    Segment(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2);
    // default constructor
    Segment() : p1(nullptr), p2(nullptr) {}

    bool equals(const Segment& seg) const;
    bool includes(const Point& point) const;
    void draw(sf::RenderWindow& window, float width = 2, sf::Color color = sf::Color::Black, bool dash = false) const;

    template<class Archive>
    void serialize(Archive & archive) {
        archive(p1, p2); // Serialize the start and end points
    }
};

#endif // SEGMENT_H
