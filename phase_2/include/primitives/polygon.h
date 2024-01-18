#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <memory>
#include <list>
#include <SFML/Graphics.hpp>
#include "primitives/point.h"
#include "primitives/segment.h"
#include "math/utils.h"

#include <cereal/archives/binary.hpp>


class Polygon {

public:
    std::vector<std::shared_ptr<Point>> points;
    std::vector<Segment> segments;
    Polygon() {}
    Polygon(std::vector<std::shared_ptr<Point>> points);
    void draw(sf::RenderWindow& window, sf::Color stroke = sf::Color::Blue, int linewidth = 2, sf::Color fill = sf::Color(0, 0, 255, 50)) const;
    void drawSegments(sf::RenderWindow& window) const;

    static void Break(Polygon& poly1, Polygon& poly2);
    static void multiBreak(std::vector<Polygon>& polygons);

    static std::vector<Segment> unionPolygons(std::vector<Polygon>& polygons);
    bool containsSegment(const Segment& segment) const;
    bool containsPoint(const Point& point) const;

    bool intersectsPoly(const Polygon& polygon) const;

    float distanceToPoint(const Point& point) const;

    float distanceToPoly(const Polygon& polygon) const;

    template<class Archive>
    void serialize(Archive& archive) {
        archive(points, segments); 
    }

private:

    

};

#endif // POLYGON_H
