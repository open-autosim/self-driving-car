#include "math/graph.h"

Graph::Graph(const std::vector<std::shared_ptr<Point>>& points, const std::vector<Segment>& segments)
    : points(points), segments(segments) {}

bool Graph::containsPoint(const Point& point) const {
    for (const auto& p : points) {
        if (p->equals(point)) {
            return true;
        }
    }
    return false;
}

void Graph::addPoint(const Point& point) {
    points.push_back(std::make_shared<Point>(point));
}

bool Graph::tryAddPoint(const Point& point) {
    if (!containsPoint(point)) {
        addPoint(point);
        return true;
    }
    return false;
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
    if (!containsSegment(segment) && !(segment.p1->equals(*segment.p2))) {
        addSegment(segment);
        return true;
    }
    return false;
}

void Graph::removeSegment(const Segment& segment) {
    auto it = std::remove_if(segments.begin(), segments.end(), 
                             [&segment](const Segment& s) { return s.equals(segment); });
    segments.erase(it, segments.end());
}

void Graph::removePoint(const Point& point) {
    auto it = std::remove_if(points.begin(), points.end(), 
                             [&point](const std::shared_ptr<Point>& p) { return p->equals(point); });
    points.erase(it, points.end());

    // Also remove associated segments
    segments.erase(std::remove_if(segments.begin(), segments.end(), 
                                  [&point](const Segment& s) { return s.includes(point); }),
                   segments.end());
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

std::shared_ptr<Point> Graph::getPoint(const Point& point) const {
    for (const auto& p : points) {
        if (p->equals(point)) {
            return p;
        }
    }
    return nullptr;
}

void Graph::draw(sf::RenderWindow& window) const {
    for (const auto& seg : segments) {
        seg.draw(window);
    }
    for (const auto& point : points) {
        point->draw(window);
    }
}

void Graph::dispose() {
    points.clear();
    segments.clear();
}

void Graph::save(const std::string& filename) const {
    std::ofstream os(filename, std::ios::binary);
    cereal::BinaryOutputArchive archive(os);
    archive(*this);  // Serialize the current object
    std::cout << "Graph saved to " << filename << std::endl;
}

bool Graph::load(const std::string& filename) {
    std::ifstream is(filename, std::ios::binary);
    if (!is) {
        std::cout << "File not found: " << filename << std::endl;
        return false; // File not found
    }
    cereal::BinaryInputArchive archive(is);
    archive(*this);  // Deserialize into the current object
    return true;
}

std::string Graph::hash() const {
    std::stringstream ss;
    {
        cereal::JSONOutputArchive archive(ss);
        archive(*this);
    }
    return ss.str();
}