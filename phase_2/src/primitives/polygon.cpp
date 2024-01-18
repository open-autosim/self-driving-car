#include "primitives/polygon.h"

Polygon::Polygon(std::vector<std::shared_ptr<Point>> points) : points(points) {

    for (int i = 1; i <= points.size(); i++) {
        segments.emplace_back(Segment(points[i - 1], points[i % points.size()]));
    }
}

void Polygon::Break(Polygon& poly1, Polygon& poly2) {
    // Convert vectors to lists

    std::list<Segment> segs1_list(poly1.segments.begin(), poly1.segments.end());
    std::list<Segment> segs2_list(poly2.segments.begin(), poly2.segments.end());

    for (auto it1 = segs1_list.begin(); it1 != segs1_list.end(); ++it1) {
        for (auto it2 = segs2_list.begin(); it2 != segs2_list.end(); ++it2) {
            std::optional<Utils::IntersectionResult> intersection = Utils::getIntersection(*it1->p1, *it1->p2, *it2->p1, *it2->p2);
            if (intersection && intersection->offset != 0.0 && intersection->offset != 1.0) {
                
                // Insert new segment after the current element in segs1_list
                auto newSegment1 = Segment(std::make_shared<Point>(intersection->point), it1->p2);
                it1->p2 = std::make_shared<Point>(intersection->point);
                it1 = segs1_list.insert(std::next(it1), newSegment1);

                // Insert new segment after the current element in segs2_list
                auto newSegment2 = Segment(std::make_shared<Point>(intersection->point), it2->p2);
                it2->p2 = std::make_shared<Point>(intersection->point);
                it2 = segs2_list.insert(std::next(it2), newSegment2);
            }
        }
    }

    // Update the original polygon segments
    poly1.segments = std::vector<Segment>(segs1_list.begin(), segs1_list.end());
    poly2.segments = std::vector<Segment>(segs2_list.begin(), segs2_list.end());

}

void Polygon::multiBreak(std::vector<Polygon>& polygons) {
    for (int i = 0; i < polygons.size()-1; i++) {
        for (int j = i + 1; j < polygons.size(); j++) {
            Break(polygons[i], polygons[j]);
        }
    }
}

std::vector<Segment> Polygon::unionPolygons(std::vector<Polygon>& polygons) {
    
    Polygon::multiBreak(polygons);

    std::vector<Segment> keptSegments;

    for (int i = 0; i < polygons.size(); i++) {
        for (auto& segment : polygons[i].segments) {
            bool keep = true;
            for (int j = 0; j < polygons.size(); j++) {
                if (i != j) {
                    if (polygons[j].containsSegment(segment)) {
                        keep = false;
                        break;
                    }
                }
            }
            if (keep) {
                keptSegments.push_back(segment);
            }
        }
    }
    return keptSegments;
}


bool Polygon::containsSegment(const Segment& segment) const {
    
    Point midPoint = Utils::average(*segment.p1, *segment.p2);
    return containsPoint(midPoint);
}

bool Polygon::containsPoint(const Point& point) const {
    
    Point outerPoint = Point(-1000, 1000);
    int intersectionCount = 0;

    for (const auto& segment : segments) {
        std::optional<Utils::IntersectionResult> intersection = Utils::getIntersection(outerPoint, point, *segment.p1, *segment.p2);
        if (intersection) {
            intersectionCount++;
        }
    }

    return intersectionCount % 2 == 1;
}

bool Polygon::intersectsPoly(const Polygon& polygon) const {
    for (const auto& s1 : segments) {
        for (const auto& s2 : polygon.segments) {
            if (Utils::getIntersection(*s1.p1, *s1.p2, *s2.p1, *s2.p2)) 
            return true;
        }
    }
    return false;
}

float Polygon::distanceToPoint(const Point& point) const {
    float minDist = std::numeric_limits<float>::max();
    for (const auto& segment : segments) {
        minDist = std::min(minDist, segment.distanceToPoint(point));
    }
    return minDist;
}

float Polygon::distanceToPoly(const Polygon& polygon) const {
    float minDist = std::numeric_limits<float>::max();
    for (const auto& point : points) {
        minDist = std::min(minDist, polygon.distanceToPoint(*point));
    }
    return minDist;
}


void Polygon::drawSegments(sf::RenderWindow& window) const {
    for (const auto& segment : segments) {
        segment.draw(window, 5, Utils::getRandomColor());
    }
}


void Polygon::draw(sf::RenderWindow& window, sf::Color stroke, int linewidth, sf::Color fill) const {
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    for (int i = 0; i < points.size(); i++) {
        polygon.setPoint(i, sf::Vector2f(points[i]->x, points[i]->y));
    }
    polygon.setOutlineColor(stroke);
    polygon.setOutlineThickness(linewidth);
    polygon.setFillColor(fill);
    window.draw(polygon);
}