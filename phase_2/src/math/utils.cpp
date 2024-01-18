#include <cmath>
#include "math/utils.h"

// Calculate the Euclidean distance between two points
float Utils::distance(const Point& p1, const Point& p2) {
    return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

// Find the nearest point to a given location within a threshold distance
std::shared_ptr<Point> Utils::getNearestPoint(const Point& loc, const std::vector<std::shared_ptr<Point>>& points, float threshold) {
    float minDist = std::numeric_limits<float>::max();
    std::shared_ptr<Point> nearest = nullptr;

    for (const auto& point : points) {
        float dist = distance(*point, loc);
        if (dist < minDist && dist < threshold) {
            minDist = dist;
            nearest = point;
        }
    }
    return nearest;
}


Point Utils::subtract(const Point& p1, const Point& p2) {
    return Point(p1.x - p2.x, p1.y - p2.y);
}

Point Utils::add(const Point& p1, const Point& p2) {
    return Point(p1.x + p2.x, p1.y + p2.y);
}

Point Utils::scale(const Point& p, float scaler) {
    return Point(p.x * scaler, p.y * scaler);
}

Point Utils::average(const Point& p1, const Point& p2) {
    return Point((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
}

Point Utils::translate(const Point& loc, float angle, float offset) {
    return Point(
        loc.x + std::cos(angle) * offset,
        loc.y + std::sin(angle) * offset
    );
}

float Utils::angle(const Point& p) {
    return std::atan2(p.y, p.x);
}

Point Utils::normalize(const Point& p) {
    return scale(p, 1.0 / magnitude(p));
}

float Utils::magnitude(const Point& p) {
    return std::hypot(p.x, p.y);
}

float Utils::dot(const Point& p1, const Point& p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

Point Utils::perpendicular(const Point& p) {
    return Point(-p.y, p.x);
}

std::optional<Utils::IntersectionResult> Utils::getIntersection(const Point& A, const Point& B, const Point& C, const Point& D) {
    float tTop = (D.x - C.x) * (A.y - C.y) - (D.y - C.y) * (A.x - C.x);
    float uTop = (C.y - A.y) * (A.x - B.x) - (C.x - A.x) * (A.y - B.y);
    float bottom = (D.y - C.y) * (B.x - A.x) - (D.x - C.x) * (B.y - A.y);

    float eps = 0.0001;

    if (std::abs(bottom) > eps) {
        float t = tTop / bottom;
        float u = uTop / bottom;
        if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) {
            // Found an intersection
            return IntersectionResult{Point{lerp(A.x, B.x, t), lerp(A.y, B.y, t)}, t};
        }
    }

    return std::nullopt; 
}



float Utils::lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

Point Utils::lerp2D(const Point& A, const Point& B, float t) {
    return Point(lerp(A.x, B.x, t), lerp(A.y, B.y, t));
}

Point Utils::get3DPoint(const Point& point, const Point& viewPoint, float height) {
    Point dir = normalize(subtract(point, viewPoint));
    float dist = distance(point, viewPoint);
    float scaler = std::atan(dist / 300) / (M_PI / 2);
    return add(point, scale(dir, height * scaler));
}

struct Color {
    float r, g, b;
};

sf::Color Utils::getRandomColor() {
    // Generate random RGB values
    sf::Uint8 red = static_cast<sf::Uint8>(rand() % 256);   // Random red (0-255)
    sf::Uint8 green = static_cast<sf::Uint8>(rand() % 256); // Random green (0-255)
    sf::Uint8 blue = static_cast<sf::Uint8>(rand() % 256);  // Random blue (0-255)

    // Return the random color
    return sf::Color(red, green, blue);
}

