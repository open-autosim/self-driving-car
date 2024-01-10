#include "utils.h"

float Utils::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

std::optional<sf::Vector2f> Utils::getIntersection(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C, const sf::Vector2f& D) {
    float tTop = (D.x - C.x) * (A.y - C.y) - (D.y - C.y) * (A.x - C.x);
    float uTop = (C.y - A.y) * (A.x - B.x) - (C.x - A.x) * (A.y - B.y);
    float bottom = (D.y - C.y) * (B.x - A.x) - (D.x - C.x) * (B.y - A.y);

    if (bottom != 0) {
        float t = tTop / bottom;
        float u = uTop / bottom;
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            return sf::Vector2f(
                Utils::lerp(A.x, B.x, t),
                Utils::lerp(A.y, B.y, t)
            );
        }
    }

    return std::nullopt;
}

float Utils::distance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    return std::sqrt(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2));
}

bool Utils::polysIntersect(const std::vector<sf::Vector2f>& poly1, const std::vector<sf::Vector2f>& poly2) {
    for (size_t i = 0; i < poly1.size(); i++) {
        for (size_t j = 0; j < poly2.size(); j++) {
            auto touch = getIntersection(
                poly1[i],
                poly1[(i + 1) % poly1.size()],
                poly2[j],
                poly2[(j + 1) % poly2.size()]
            );

            if (touch.has_value()) {
                return true;
            }
        }
    }
    return false;
}

