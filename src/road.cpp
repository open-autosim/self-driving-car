#include "road.h"
#include <algorithm>
#include <cmath>
#include "utils.h"

const int MAX_INT = 20000;

Road::Road(float x, float width, int laneCount)
    : x(x), width(width), laneCount(laneCount) {
    left = x - width / 2;
    right = x + width / 2;

    // Define the road borders
    borders.push_back(sf::Vector2f(left, -MAX_INT));  // Top left
    borders.push_back(sf::Vector2f(left, MAX_INT));   // Bottom left
    borders.push_back(sf::Vector2f(right, -MAX_INT)); // Top right
    borders.push_back(sf::Vector2f(right, MAX_INT));  // Bottom right
}

float Road::getLaneCenter(int laneIndex) {
    float laneWidth = width / laneCount;
    return left + laneWidth / 2 + std::min(laneIndex, laneCount - 1) * laneWidth;
}

void Road::draw(sf::RenderWindow& window) {
    // Line thickness and margins
    float thickness = 5.0f;
    float margin = 8.0f; // Margin between the road edge and the border line

    // Road surface
    sf::RectangleShape roadSurface(sf::Vector2f(width, MAX_INT));
    roadSurface.setPosition(left, -10000);
    roadSurface.setFillColor(sf::Color(220, 220, 220));
    window.draw(roadSurface);

    // Draw lane markings (dashed lines) using lerp
    for (int i = 1; i <= laneCount - 1; ++i) {
        float x = Utils::lerp(left + margin, right - margin, i / static_cast<float>(laneCount));
        for (float y = -10000; y < 10000; y += 40) {
            sf::RectangleShape line(sf::Vector2f(thickness, 20));
            line.setPosition(x - thickness / 2, y);
            line.setFillColor(sf::Color::White);
            window.draw(line);
        }
    }

    // Draw solid border lines with margin
    sf::RectangleShape leftBorder(sf::Vector2f(thickness, 20000));
    leftBorder.setPosition(left + margin, -10000);
    leftBorder.setFillColor(sf::Color::White);
    window.draw(leftBorder);

    sf::RectangleShape rightBorder(sf::Vector2f(thickness, 20000));
    rightBorder.setPosition(right - margin - thickness, -10000);
    rightBorder.setFillColor(sf::Color::White);
    window.draw(rightBorder);
}



// void Road::draw(sf::RenderWindow& window) {
//     // Line thickness and margins
//     float thickness = 5.0f;
//     float margin = 10.0f; // Margin between the road edge and the border line

//     // Adjusted road width considering margins
//     float adjustedRoadWidth = width - 2 * margin;
//     float laneWidth = adjustedRoadWidth / laneCount;

//     // Road surface
//     sf::RectangleShape roadSurface(sf::Vector2f(width, 20000));
//     roadSurface.setPosition(left, -10000);
//     roadSurface.setFillColor(sf::Color(220, 220, 220));
//     window.draw(roadSurface);

//     // Draw lane markings (dashed lines)
//     for (int i = 1; i <= laneCount - 1; ++i) {
//         float x = left + margin + laneWidth * i;
//         for (float y = -10000; y < 10000; y += 40) {
//             sf::RectangleShape line(sf::Vector2f(thickness, 20));
//             line.setPosition(x - thickness / 2, y);
//             line.setFillColor(sf::Color::White);
//             window.draw(line);
//         }
//     }

//     // Draw solid border lines with margin
//     sf::RectangleShape leftBorder(sf::Vector2f(thickness, 20000));
//     leftBorder.setPosition(left + margin, -10000);
//     leftBorder.setFillColor(sf::Color::White);
//     window.draw(leftBorder);

//     sf::RectangleShape rightBorder(sf::Vector2f(thickness, 20000));
//     rightBorder.setPosition(right - margin - thickness, -10000);
//     rightBorder.setFillColor(sf::Color::White);
//     window.draw(rightBorder);
// }


