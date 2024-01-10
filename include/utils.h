#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <optional>

class Utils {
public:
    static float lerp(float a, float b, float t);
    static std::optional<sf::Vector2f> getIntersection(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& C, const sf::Vector2f& D);
    static float distance(const sf::Vector2f& A, const sf::Vector2f& B);
    static bool polysIntersect(const std::vector<sf::Vector2f>& poly1, const std::vector<sf::Vector2f>& poly2);


};

#endif // UTILS_H
