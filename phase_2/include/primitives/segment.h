#ifndef SEGMENT_H
#define SEGMENT_H

#include <memory>
#include <functional>
#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include "primitives/point.h"
#include "math/utils.h"

class Segment {
public:
    std::shared_ptr<Point> p1;
    std::shared_ptr<Point> p2;

    Segment(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2);
    // default constructor
    Segment() : p1(nullptr), p2(nullptr) {}

    bool equals(const Segment& seg) const;
    bool includes(const Point& point) const;
    void draw(sf::RenderWindow& window, float width = 2, sf::Color color = sf::Color::Black, bool dash = false, float dashLength = 10.0f, float gapLength = 10.0f) const;


    float length() const {
        return Utils::distance(*p1, *p2);
    }

    Point directionVector() const {
        return Utils::normalize(Utils::subtract(*p2, *p1));
    }

    float distanceToPoint(const Point& point) const;

    Utils::IntersectionResult projectPoint(const Point& point) const; 

    static std::shared_ptr<Segment> getNearestSegment(const Point& loc, const std::vector<Segment>& segments, float threshold = std::numeric_limits<float>::max());


    template<class Archive>
    void serialize(Archive & archive) {
        archive(p1, p2); // Serialize the start and end points
    }

};


#endif // SEGMENT_H
