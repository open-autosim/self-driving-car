#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <limits>
#include <memory> // for std::shared_ptr
#include <optional>
#include <random>
#include "primitives/point.h"


class Utils {
public:
    static float distance(const Point& p1, const Point& p2);
    static std::shared_ptr<Point> getNearestPoint(const Point& loc, const std::vector<std::shared_ptr<Point>>& points, float threshold = std::numeric_limits<float>::max());

    static Point subtract(const Point& p1, const Point& p2);
    static Point add(const Point& p1, const Point& p2);
    static Point scale(const Point& p, float scaler);

    static Point average(const Point& p1, const Point& p2);
    static Point translate(const Point& loc, float angle, float offset);
    static float angle(const Point& p);

    static Point normalize(const Point& p);
    static float magnitude(const Point& p);

    static float dot(const Point& p1, const Point& p2);

    static Point perpendicular(const Point& p);

    static float getRand() {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);
        return dis(gen);
    }

    struct IntersectionResult {
        Point point;
        float offset;
    };

    static std::optional<IntersectionResult> getIntersection(const Point& A, const Point& B, const Point& C, const Point& D);


    static float lerp(float a, float b, float t);
    static Point lerp2D(const Point& A, const Point& B, float t);

    static Point get3DPoint(const Point& point, const Point& viewPoint, float height);

    sf::Color static getRandomColor();

};

#endif // UTILS_H
