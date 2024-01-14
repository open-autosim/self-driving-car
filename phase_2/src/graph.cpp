#include "graph.h"

Graph::Graph(const std::vector<Point>& points, const std::vector<Segment>& segments) : points(points), segments(segments) {}

void Graph::draw(sf::RenderWindow& window) const {
    for (const auto& seg : segments) {
        seg.draw(window);
    }
    for (const auto& point : points) {
        point.draw(window);
    }
}
