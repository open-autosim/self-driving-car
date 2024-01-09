#include "road.h"
#include <algorithm>
#include <cmath>
#include "utils.h"

Road::Road(float x, float width, int laneCount)
    : x(x), width(width), laneCount(laneCount) {
    left = x - width / 2;
    right = x + width / 2;

    // Define the road borders
    borders.push_back(sf::Vector2f(left, -10000));  // Top left
    borders.push_back(sf::Vector2f(left, 10000));   // Bottom left
    borders.push_back(sf::Vector2f(right, -10000)); // Top right
    borders.push_back(sf::Vector2f(right, 10000));  // Bottom right
}

float Road::getLaneCenter(int laneIndex) {
    float laneWidth = width / laneCount;
    return left + laneWidth / 2 + std::min(laneIndex, laneCount - 1) * laneWidth;
}


void Road::draw(sf::RenderWindow& window) {
    // Line thickness
    float thickness = 5.0f;

    // Road surface
    sf::RectangleShape roadSurface(sf::Vector2f(width, 20000)); // Height to cover the road length
    roadSurface.setPosition(left, -10000); // Position it to cover the road area
    roadSurface.setFillColor(sf::Color(220, 220, 220)); // Light gray color for the road
    window.draw(roadSurface);

    // Draw lane markings (dashed lines)
    for (int i = 1; i <= laneCount - 1; ++i) {
        float x = Utils::lerp(left, right, i / static_cast<float>(laneCount));
        for (float y = -10000; y < 10000; y += 40) { // 40 is the sum of line length and gap
            sf::RectangleShape line(sf::Vector2f(thickness, 20)); // 20 is the line length
            line.setPosition(x - thickness / 2, y);
            line.setFillColor(sf::Color::White);
            window.draw(line);
        }
    }

    // Draw solid border lines
    for (size_t i = 0; i < borders.size(); i += 2) {
        sf::RectangleShape line;
        line.setSize(sf::Vector2f(thickness, 20000)); // 20000 to cover the borders length
        line.setPosition(borders[i].x - thickness / 2, borders[i].y);
        line.setFillColor(sf::Color::White);
        window.draw(line);
    }
}

// void Road::draw(sf::RenderWindow& window) {
//     sf::VertexArray lines(sf::Lines);

//     // Draw lane markings
//     for (int i = 1; i <= laneCount - 1; ++i) {
//         float x = Utils::lerp(left, right, i / static_cast<float>(laneCount));
//         lines.append(sf::Vertex(sf::Vector2f(x, -10000), sf::Color::White));
//         lines.append(sf::Vertex(sf::Vector2f(x, 10000), sf::Color::White));
//     }

//     // Draw road borders
//     for (size_t i = 0; i < borders.size(); i += 2) {
//         lines.append(sf::Vertex(borders[i], sf::Color::White));
//         lines.append(sf::Vertex(borders[i + 1], sf::Color::White));
//     }

//     window.draw(lines);
// }

