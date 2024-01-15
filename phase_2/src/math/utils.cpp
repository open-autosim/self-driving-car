#include "math/utils.h"
#include <cmath>

// Calculate the Euclidean distance between two points
double Utils::distance(const Point& p1, const Point& p2) {
    return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

// Find the nearest point to a given location within a threshold distance
std::shared_ptr<Point> Utils::getNearestPoint(const Point& loc, const std::vector<std::shared_ptr<Point>>& points, double threshold) {
    double minDist = std::numeric_limits<double>::max();
    std::shared_ptr<Point> nearest = nullptr;

    for (const auto& point : points) {
        double dist = distance(*point, loc);
        if (dist < minDist && dist < threshold) {
            minDist = dist;
            nearest = point;
        }
    }

    return nearest;
}
