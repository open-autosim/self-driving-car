#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include "primitives/segment.h"

class Graph {
    std::vector<std::shared_ptr<Point>> points;
    std::vector<Segment> segments;

public:
    Graph(const std::vector<std::shared_ptr<Point>>& points, const std::vector<Segment>& segments);

    const std::vector<std::shared_ptr<Point>>& getPoints() const { return points; }
    std::vector<Segment>& getSegments() { return segments; }

    std::shared_ptr<Point> getPoint(const Point& point) const;
    bool containsPoint(const Point& point) const;
    void addPoint(const Point& point);
    bool tryAddPoint(const Point& point);
    bool containsSegment(const Segment& segment) const;
    void addSegment(const Segment& segment);
    bool tryAddSegment(const Segment& segment);
    void removeSegment(const Segment& segment);
    void removePoint(const Point& point);
    std::vector<Segment> getSegmentsWithPoint(const Point& point) const;

    void draw(sf::RenderWindow& window) const;

    void dispose(); 
};

#endif // GRAPH_H
