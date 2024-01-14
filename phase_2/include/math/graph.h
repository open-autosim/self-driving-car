#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "primitives/segment.h"

class Graph {
    std::vector<Point> points;
    std::vector<Segment> segments;

public:
    Graph(const std::vector<Point>& points, const std::vector<Segment>& segments);

    std::vector<Point> getPoints() const { return points; }
    std::vector<Segment> getSegments() const { return segments; }

    bool containsPoint(const Point& point) const;
    void addPoint(const Point& point);
    bool tryAddPoint(const Point& point);
    bool containsSegment(const Segment& segment) const;
    void addSegment(const Segment& segment);
    bool tryAddSegment(const Segment& segment);
    void removeSegment(const Segment& segment);
    void removePoint(const Point& point);
    std::vector<Segment> getSegmentsWithPoint(const Point& point) const;
    void dispose();

    void draw(sf::RenderWindow& window) const;
};

#endif // GRAPH_H
