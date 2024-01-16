#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <limits>
#include <memory> // for std::shared_ptr
#include "primitives/point.h"

class Utils {
public:
    static double distance(const Point& p1, const Point& p2);
    static std::shared_ptr<Point> getNearestPoint(const Point& loc, const std::vector<std::shared_ptr<Point>>& points, double threshold = std::numeric_limits<double>::max());
    static Point subtract(const Point& p1, const Point& p2);
    static Point add(const Point& p1, const Point& p2);
    static Point scale(const Point& p, double scaler);
};

#endif // UTILS_H
