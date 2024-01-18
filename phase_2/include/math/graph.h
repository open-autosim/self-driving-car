#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include "primitives/segment.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <functional>
#include <fstream>
#include <cereal/archives/json.hpp>
#include <sstream>

class Graph {
    std::vector<std::shared_ptr<Point>> points;
    std::vector<Segment> segments;

public:
    Graph(const std::vector<std::shared_ptr<Point>>& points, const std::vector<Segment>& segments);
    // add default constructor
    Graph() {}

    const std::vector<std::shared_ptr<Point>>& getPoints() const { return points; }
    const std::vector<Segment>& getSegments() const { return segments; } // Public getter for segments

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


    template<class Archive>
    void serialize(Archive & archive) {
        archive(points, segments); // Serialize the points and segments
    }

    void save(const std::string& filename) const;
    bool load(const std::string& filename);

    std::string hash() const;

    // custom hash for graph

};


#endif // GRAPH_H
