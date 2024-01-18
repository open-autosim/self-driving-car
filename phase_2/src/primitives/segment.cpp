#include "primitives/segment.h"

Segment::Segment(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2) : p1(p1), p2(p2) {}

bool Segment::equals(const Segment& seg) const {
    return includes(*seg.p1) && includes(*seg.p2);
}

bool Segment::includes(const Point& point) const {
    return (p1->equals(point) || p2->equals(point));
}

float Segment::distanceToPoint(const Point& point) const {

    Utils::IntersectionResult proj = projectPoint(point);
    if (proj.offset > 0 && proj.offset < 1) {
        return Utils::distance(point, proj.point);
    }
    float distToP1 = Utils::distance(point, *p1);
    float distToP2 = Utils::distance(point, *p2);
    return std::min(distToP1, distToP2);

}

std::shared_ptr<Segment> Segment::getNearestSegment(const Point& loc, const std::vector<Segment>& segments, float threshold) {
    
    float minDist = std::numeric_limits<float>::max();
    std::shared_ptr<Segment> nearest = nullptr;

    for (const auto& segment : segments) {
        float dist = segment.distanceToPoint(loc); // Assuming Segment has a distanceToPoint method
        if (dist < minDist && dist < threshold) {
            minDist = dist;
            nearest = std::make_shared<Segment>(segment); // Create a new shared_ptr for the nearest segment
        }
    }
    return nearest;
}


Utils::IntersectionResult Segment::projectPoint(const Point& point) const {
    
    Point a = Utils::subtract(point, *p1);
    Point b = Utils::subtract(*p2, *p1);
    Point normB = Utils::normalize(b);
    float scaler = Utils::dot(a, normB);
    Utils::IntersectionResult result;
    result.point = Utils::add(*p1, Utils::scale(normB, scaler));
    result.offset = scaler / Utils::magnitude(b);
    
    return result;

}

void Segment::draw(sf::RenderWindow& window, float width, sf::Color color, bool dash, float dashLength, float gapLength) const {
    sf::Vector2f delta = sf::Vector2f(p2->x - p1->x, p2->y - p1->y);
    float length = std::hypot(delta.x, delta.y);

    if (!dash) {
        // Draw solid line with width
        sf::RectangleShape line(sf::Vector2f(length, width));
        line.setPosition(sf::Vector2f(p1->x, p1->y));
        line.setFillColor(color);
        float angle = std::atan2(delta.y, delta.x) * 180.0f / M_PI;
        line.setRotation(angle);
        window.draw(line);
    } else {
        // Draw dashed line
        const float dashLength = 11.0f; // Dash length
        const float gapLength = 11.0f;  // Gap length

        sf::Vector2f unitDelta = delta / length;
        float currentLength = 0.0f;

        while (currentLength < length) {
            sf::Vector2f startPos = sf::Vector2f(p1->x, p1->y) + unitDelta * currentLength;
            currentLength += dashLength;
            if (currentLength > length) currentLength = length;
            sf::Vector2f endPos = sf::Vector2f(p1->x, p1->y) + unitDelta * currentLength;
            currentLength += gapLength;

            sf::RectangleShape dash(sf::Vector2f(std::hypot(endPos.x - startPos.x, endPos.y - startPos.y), width));
            dash.setPosition(startPos);
            dash.setFillColor(color);
            float dashAngle = std::atan2(endPos.y - startPos.y, endPos.x - startPos.x) * 180.0f / M_PI;
            dash.setRotation(dashAngle);

            window.draw(dash);
        }
    }
}
