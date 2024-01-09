#include <iostream>
#include "car.h"
#include <cmath>

Car::Car(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), speed(0), acceleration(0.2), maxSpeed(3), friction(0.05), angle(0) {
    
    shape.setFillColor(sf::Color::Blue);

    if (!texture.loadFromFile("include/car.png")) {
        std::cerr << "Error: Unable to load car texture!" << std::endl;
        // Handle the error (for example, by exiting the program)
        exit(EXIT_FAILURE);
    }

    shape.setTexture(&texture); // Use the texture object directly

    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width / 2, height / 2);
    shape.setPosition(x, y);
}

void Car::update() {

    controls.update(); 
    move();
}

#include <iostream>
#include <cmath>


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
        if (controls.left) {
            angle += 0.03 * flip;
        }
        if (controls.right) {
            angle -= 0.03 * flip;
        }
    }

    // Normalize the angle to range [0, 2π]
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0) {
        angle += 2 * M_PI;
    }

    // Update position
    x -= std::sin(angle) * speed;
    y -= std::cos(angle) * speed;

    // Update shape position and rotation
    shape.setPosition(x, y);
    shape.setRotation(-angle * 180 / M_PI); // Convert radians to degrees

}

void Car::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
