#include "sensor.h"
#include "utils.h"
#include "car.h"
#include <algorithm>
#include <cmath>

Sensor::Sensor(Car& car) : m_car(car), rayCount(5), rayLength(150), raySpread(M_PI / 2) {}

void Sensor::update(const std::vector<sf::Vector2f>& borders) {
    castRays();
    readings.clear();

    // Convert points to line segments
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> segments;
    for (size_t i = 0; i < borders.size(); i += 2) {
        if (i + 1 < borders.size()) {
            segments.push_back(std::make_pair(borders[i], borders[i + 1]));
        }
    }

    for (auto& ray : rays) {
        readings.push_back(getReading(ray, segments));
    }
   
}


void Sensor::draw(sf::RenderWindow& window) {
    float lineWidth = 2.0f; // Set your desired line width

    for (size_t i = 0; i < rays.size(); i++) {
        // Draw the first part of the ray in yellow
        sf::Vector2f end = readings[i] ? *readings[i] : rays[i].second;
        drawThickLine(window, rays[i].first, end, sf::Color::Yellow, lineWidth);

        // If there is an intersection, draw the second part of the ray in black
        if (readings[i]) {
            drawThickLine(window, *readings[i], rays[i].second, sf::Color::Black, lineWidth);
        }
    }
}

void Sensor::drawThickLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, sf::Color color, float thickness) {
    sf::RectangleShape line;
    line.setFillColor(color);
    float length = std::hypot(end.x - start.x, end.y - start.y);
    line.setSize(sf::Vector2f(length, thickness));
    line.setOrigin(0, thickness / 2);
    line.setPosition(start);
    line.setRotation(std::atan2(end.y - start.y, end.x - start.x) * 180 / M_PI);
    window.draw(line);
}

// void Sensor::draw(sf::RenderWindow& window) {
//     for (size_t i = 0; i < rays.size(); i++) {
//         sf::Vertex line[] = {
//             sf::Vertex(rays[i].first),
//             sf::Vertex(readings[i] ? *readings[i] : rays[i].second)
//         };

//         line[0].color = sf::Color::Yellow;
//         line[1].color = readings[i] ? sf::Color::Black : sf::Color::Yellow;
//         window.draw(line, 2, sf::Lines);
//     }
// }

void Sensor::castRays() {
    rays.clear();
    for (int i = 0; i < rayCount; i++) {
        float rayAngle = Utils::lerp(raySpread / 2, -raySpread / 2, rayCount == 1 ? 0.5f : static_cast<float>(i) / (rayCount - 1)) + m_car.getAngle();
        sf::Vector2f start(m_car.getX(), m_car.getY());
        sf::Vector2f end(start.x - std::sin(rayAngle) * rayLength, start.y - std::cos(rayAngle) * rayLength);
        rays.push_back(std::make_pair(start, end));
    }
}


sf::Vector2f* Sensor::getReading(const std::pair<sf::Vector2f, sf::Vector2f>& ray, const std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& roadBorders) {
    std::vector<sf::Vector2f> touches;
    for (const auto& border : roadBorders) {
        std::optional<sf::Vector2f> touch = Utils::getIntersection(ray.first, ray.second, border.first, border.second);
        if (touch.has_value()) {
            touches.push_back(touch.value());
        }
    }

    if (touches.empty()) {
        return nullptr;
    } else {
        auto minIt = std::min_element(touches.begin(), touches.end(),
            [&ray](const sf::Vector2f& a, const sf::Vector2f& b) {
                return Utils::distance(ray.first, a) < Utils::distance(ray.first, b);
            });
        return new sf::Vector2f(*minIt); // Dynamically allocate memory for the closest intersection
    }
}
