#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "segment.h"

class Graph {
    std::vector<Point> points;
    std::vector<Segment> segments;

public:
    Graph(const std::vector<Point>& points, const std::vector<Segment>& segments);

    void draw(sf::RenderWindow& window) const;
};

#endif // GRAPH_H
