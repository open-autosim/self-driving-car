#include <iostream>
#include "car.h"
#include "utils.h"
#include <cmath>

Car::Car(float x, float y, float width, float height, float roadLeft, float roadRight, std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders)
    : x(x), y(y), width(width), height(height), 
    speed(0), acceleration(0.2), maxSpeed(3), 
    friction(0.05), angle(0), 
    roadLeft(roadLeft), roadRight(roadRight), borders(borders),
    sensor(*this) {

    // if (!texture.loadFromFile("include/car.png")) {
    //     std::cerr << "Error: Unable to load car texture!" << std::endl;
    //     // Handle the error (for example, by exiting the program)
    //     exit(EXIT_FAILURE);
    // }

    // shape.setTexture(&texture); // Use the texture object directly

    // shape.setSize(sf::Vector2f(width, height));
    // shape.setOrigin(width / 2, height / 2);
    // shape.setPosition(x, y);

    // Create the polygon shape
    polygonShape.setPointCount(4);
    polygonShape.setFillColor(sf::Color::Red);
    
    

    
    
}
void Car::update() {

    
    controls.update(); 
    move();
    createPolygon();
        // assessDamage();
    
    sensor.update(borders);
}

// void Car::assessDamage() {
    
//     for (int i = 0; i < borders.size() - 1; i++) { // Ensure we don't go out of bounds
//         if (Utils::polysIntersect(polygon, {borders[i], borders[i + 1]})) {
//             //print borders all border
//             std::cout << "Borders: " << std::endl;
//             for (auto& point : borders) {
//                 std::cout << point.x << ", " << point.y << std::endl;
//             }
//             std::cout << "Collision detected!" << std::endl;
//             crashed = true;   
//             return; 
//         }
//     }
//     crashed = false;
// }

void Car::createPolygon() {

    polygon.clear(); 
    float rad = std::hypot(width, height) / 2;
    float alpha = std::atan2(width, height);

    polygon.push_back(sf::Vector2f(x - std::sin(angle - alpha) * rad, y - std::cos(angle - alpha) * rad));
    polygon.push_back(sf::Vector2f(x - std::sin(angle + alpha) * rad, y - std::cos(angle + alpha) * rad));
    polygon.push_back(sf::Vector2f(x - std::sin(M_PI + angle - alpha) * rad, y - std::cos(M_PI + angle - alpha) * rad));
    polygon.push_back(sf::Vector2f(x - std::sin(M_PI + angle + alpha) * rad, y - std::cos(M_PI + angle + alpha) * rad));

    for (int i = 0; i < polygon.size(); i++) {
        polygonShape.setPoint(i, polygon[i]);

    }

    std::cout << "Polygon: " << std::endl;
    for (auto& point : polygon) {
        std::cout << "Point: (" << point.x << ", " << point.y << ")" << std::endl;
    }

    sf::Vector2f bottomLeft = polygon[0];
    sf::Vector2f bottomRight = polygon[1];
    sf::Vector2f topLeft = polygon[3];
    sf::Vector2f topRight = polygon[2];

    std::cout << "Bottom Left: (" << bottomLeft.x << ", " << bottomLeft.y << ")" << std::endl;
    std::cout << "Bottom Right: (" << bottomRight.x << ", " << bottomRight.y << ")" << std::endl;
    std::cout << "Top Left: (" << topLeft.x << ", " << topLeft.y << ")" << std::endl;
    std::cout << "Top Right: (" << topRight.x << ", " << topRight.y << ")" << std::endl;
}


void Car::move() {
    // Forward movement
    if (controls.forward) {
        speed += acceleration;
    }

    // Backward movement
    if (controls.reverse) {
        speed -= acceleration;
    }

    // Ensure the car doesn't exceed the maximum speed or go below minimum reverse speed
    if (speed > maxSpeed) {
        speed = maxSpeed;
    }
    if (speed < -maxSpeed / 2) {
        speed = -maxSpeed / 2;
    }

    // Apply friction to slow down the car
    if (!controls.forward && !controls.reverse) {
        if (speed > 0) {
            speed -= friction;
        } else if (speed < 0) {
            speed += friction;
        }

        // Stop the car if the speed is below the friction threshold
        if (std::abs(speed) < friction) {
            speed = 0;
        }
    }

    // Rotation logic with speed check
    if (speed != 0) {
        float flip = speed > 0 ? 1 : -1;
        float turningRate = 0.01 * std::abs(speed);
        if (controls.left) {
            angle += turningRate * flip;
        }
        if (controls.right) {
            angle -= turningRate * flip;
        }
    }

    // Normalize the angle to range [0, 2π]
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0) {
        angle += 2 * M_PI;
    }

    // Update position with provisional values
    x -= std::sin(angle) * speed;
    y -= std::cos(angle) * speed;
    

    // Update shape position and rotation
    // shape.setPosition(x, y);
    // shape.setRotation(-angle * 180 / M_PI); 

    // polygonShape.setPosition(x, y);
    // polygonShape.setRotation(-angle * 180 / M_PI);

}

void Car::draw(sf::RenderWindow& window) {

    window.draw(polygonShape);

    sensor.draw(window);
}