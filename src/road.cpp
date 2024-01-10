#include "road.h"
#include <algorithm>
#include <cmath>
#include "utils.h"

const int MAX_INT = 20000;

Road::Road(float center, float width, int laneCount)
    : center(center), width(width), laneCount(laneCount) {
    left = center - width / 2;
    right = center + width / 2;

    // Define the road borders
    borders.emplace_back(sf::Vector2f(left + margin, -MAX_INT), sf::Vector2f(left + margin, MAX_INT));   // Left border
    borders.emplace_back(sf::Vector2f(right - margin, -MAX_INT), sf::Vector2f(right - margin, MAX_INT)); // Right border
}

float Road::getLaneCenter(int laneIndex) {
    float laneWidth = width / laneCount;
    return left + laneWidth / 2 + std::min(laneIndex, laneCount - 1) * laneWidth;
}

void Road::draw(sf::RenderWindow& window) {
    // Line thickness and margins
    float thickness = 5.0f;

    // Road surface
    sf::RectangleShape roadSurface(sf::Vector2f(width, MAX_INT * 2));
    roadSurface.setPosition(left, -MAX_INT);
    roadSurface.setFillColor(sf::Color(220, 220, 220));
    window.draw(roadSurface);

    // Draw lane markings (dashed lines) using lerp
    for (int i = 1; i <= laneCount - 1; ++i) {
        float x = Utils::lerp(left + margin, right - margin, i / static_cast<float>(laneCount));
        for (float y = -MAX_INT; y < MAX_INT; y += 40) {
            sf::RectangleShape line(sf::Vector2f(thickness, 20));
            line.setPosition(x - thickness / 2, y);
            line.setFillColor(sf::Color::White);
            window.draw(line);
        }
    }

    // Draw solid border lines with margin
    for (const auto& border : borders) {
        sf::RectangleShape borderLine(sf::Vector2f(thickness, MAX_INT * 2));
        borderLine.setPosition(border.first.x - thickness / 2, -MAX_INT);  // Adjust the position by subtracting half of the thickness
        borderLine.setFillColor(sf::Color::White);
        window.draw(borderLine);
    }

}