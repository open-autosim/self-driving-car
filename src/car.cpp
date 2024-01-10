#include <iostream>
#include "car.h"
#include "utils.h"
#include <cmath>

Car::~Car() {
    delete sensor; // Delete the sensor in the destructor
}

Car::Car(float x, float y, float width, float height, float roadLeft, float roadRight, 
std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders, std::string controlsType, int maxSpeed)
    : x(x), y(y), width(width), height(height), 
    speed(0), acceleration(0.2), maxSpeed(maxSpeed), 
    friction(0.05), angle(0), 
    roadLeft(roadLeft), roadRight(roadRight), borders(borders), 
    controls(controlsType),
    sensor(controlsType == "DUMMY" ? nullptr : new Sensor(*this)) {

    // if (!texture.loadFromFile("include/car.png")) {
    //     std::cerr << "Error: Unable to load car texture!" << std::endl;
    //     // Handle the error (for example, by exiting the program)
    //     exit(EXIT_FAILURE);
    // }

    // polygonShape.setTexture(&texture); // Use the texture object directly

    // shape.setSize(sf::Vector2f(width, height));
    // shape.setOrigin(width / 2, height / 2);
    // shape.setPosition(x, y);

    // Create the polygon shape
    polygonShape.setPointCount(4);
    polygonShape.setFillColor(sf::Color::Red);
    
}
void Car::update() {

    if (!damaged) {
        controls.update(); 
        move();
        createPolygon();
        assessDamage();
    }

    if (sensor != nullptr) {
        sensor->update(borders);
    }
}

void Car::assessDamage() {
    
    for (int i = 0; i < borders.size(); i++) { // Ensure we don't go out of bounds
        if (Utils::polysIntersect(polygon, {borders[i].first, borders[i].second})) {
            std::cout << "Collision detected!" << std::endl;
            damaged = true;   
            return; 
        }
    }
    damaged = false;
}

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
}


void Car::move() {
    
    if (controls.forward) {
        speed += acceleration;
    }
    if (controls.reverse) {
        speed -= acceleration;
    }
    if (speed > maxSpeed) {
        speed = maxSpeed;
    }
    if (speed < -maxSpeed / 2) {
        speed = -maxSpeed / 2;
    }
    if (!controls.forward && !controls.reverse) {
        if (speed > 0) {
            speed -= friction;
        } else if (speed < 0) {
            speed += friction;
        }
        if (std::abs(speed) < friction) {
            speed = 0;
        }
    }
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

    x -= std::sin(angle) * speed;
    y -= std::cos(angle) * speed;

}

void Car::draw(sf::RenderWindow& window) {


    if (damaged) {
        polygonShape.setFillColor(sf::Color(190,190,190));
    } else {
        polygonShape.setFillColor(sf::Color::Blue);
    }

    window.draw(polygonShape);
    if (sensor != nullptr) {
        sensor->draw(window);
    }
}