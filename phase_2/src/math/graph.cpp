#include "math/graph.h"

Graph::Graph(const std::vector<Point>& points, const std::vector<Segment>& segments) : points(points), segments(segments) {}



bool Graph::containsPoint(const Point& point) const {
    
    for (const auto& p : points) {
        if (p.equals(point)) {
            return true;
        }
    }
    return false;
}


bool Graph::tryAddPoint(const Point& point) {
    if (!containsPoint(point)) {
        addPoint(point);
        return true;
    }
    return false;
}


void Graph::addPoint(const Point& point) {
    points.push_back(point);
}

bool Graph::containsSegment(const Segment& segment) const {
    for (const auto& seg : segments) {
        if (seg.equals(segment)) {
            return true;
        }
    }
    return false;
}

void Graph::addSegment(const Segment& segment) {
    segments.push_back(segment);
}

bool Graph::tryAddSegment(const Segment& segment) {
    if (!containsSegment(segment) && !segment.p1.equals(segment.p2)) {
        addSegment(segment);
        return true;
    }
    return false;
}

void Graph::removeSegment(const Segment& segment) {
    for (auto it = segments.begin(); it != segments.end(); ++it) {
        if (it->equals(segment)) {
            segments.erase(it);
            return;
        }
    }
}

void Graph::removePoint(const Point& point) {

    std::vector<Segment> segs = getSegmentsWithPoint(point);

    for (const auto& seg : segs) {
        removeSegment(seg);
    }

    for (auto it = points.begin(); it != points.end(); ++it) {
        if (it->equals(point)) {
            points.erase(it);
            return;
        }
    }
}

std::vector<Segment> Graph::getSegmentsWithPoint(const Point& point) const {
    std::vector<Segment> segs;
    for (const auto& seg : segments) {
        if (seg.includes(point)) {
            segs.push_back(seg);
        }
    }
    return segs;
}

void Graph::dispose() {
    points.clear();
    segments.clear();
}

void Graph::draw(sf::RenderWindow& window) const {
    for (const auto& seg : segments) {
        seg.draw(window);
    }
    for (const auto& point : points) {
        point.draw(window);
    }
}
