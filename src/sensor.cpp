#include "sensor.h"
#include "utils.h"
#include "car.h"
#include <algorithm>
#include <cmath>

Sensor::Sensor(Car& car) : m_car(car), rayCount(5), rayLength(150), raySpread(M_PI / 2) {}

void Sensor::update(const std::vector<std::pair<sf::Vector2f, sf::Vector2f>>& roadBorders) {
    castRays();
    readings.clear();

    for (auto& ray : rays) {
        readings.push_back(getReading(ray, roadBorders));
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

void Sensor::castRays() {
    rays.clear();
    for (int i = 0; i < rayCount; i++) {
        float rayAngle = Utils::lerp(raySpread / 2, -raySpread / 2, rayCount == 1 ? 0.5f : static_cast<float>(i) / (rayCount - 1)) + m_car.getAngle();
        sf::Vector2f start(m_car.getX(), m_car.getY());
        sf::Vector2f end(start.x - std::sin(rayAngle) * rayLength, start.y - std::cos(rayAngle) * rayLength);
        rays.push_back(std::make_pair(start, end));
    }
}


void Sensor::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < rays.size(); i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(rays[i].first.x, rays[i].first.y)),
            sf::Vertex(sf::Vector2f(rays[i].second.x, rays[i].second.y))
        };

        line[0].color = sf::Color::Yellow;
        line[1].color = sf::Color::Yellow;

        window.draw(line, 2, sf::Lines);

        if (readings[i]) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(readings[i]->x, readings[i]->y)),
                sf::Vertex(sf::Vector2f(rays[i].second.x, rays[i].second.y))
            };

            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;

            window.draw(line, 2, sf::Lines);
        }
    }
}


