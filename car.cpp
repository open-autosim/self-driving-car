#include "car.h"
#include <cmath>

Car::Car(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), speed(0), acceleration(0.2), maxSpeed(3), friction(0.05), angle(0) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width / 2, height / 2);
    shape.setPosition(x, y);
}

void Car::update(const sf::RenderWindow& window) {
    controls.update(window);  // Pass sf::RenderWindow
    move();
}

void Car::move() {
    // Implement movement logic here based on controls

    // Example of forward movement
    if (controls.forward) {
        speed += acceleration;
    }
    // Add other movement logic

    // Update position
    x -= std::sin(angle) * speed;
    y -= std::cos(angle) * speed;

    shape.setPosition(x, y);
    shape.setRotation(-angle * 180 / 3.14159); // Convert radians to degrees
}

void Car::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
