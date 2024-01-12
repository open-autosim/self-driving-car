#include <iostream>
#include "car.h"
#include "utils.h"
#include <cmath>
#include <vector>
#include <memory> // for std::unique_ptr

int Car::nextID = 1;

Car::~Car() {
    // sensor is managed by unique_ptr, no need for manual deletion
}

Car::Car(float x, float y, float width, float height, float roadLeft, float roadRight, 
std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders, std::string controlsType, int maxSpeed, int id)
    : x(x), y(y), width(width), height(height), 
    speed(0), acceleration(0.2), maxSpeed(maxSpeed), 
    friction(0.05), angle(0), 
    roadLeft(roadLeft), roadRight(roadRight), borders(std::move(borders)), 
    controls(controlsType), controlsType(controlsType),
    sensor(controlsType == "DUMMY" ? nullptr : std::make_unique<Sensor>(*this)), id(id) {
    
    nextID++;

    // Create the polygon shape
    polygonShape.setPointCount(4);
    polygonShape.setFillColor(sf::Color::Red);
    
    // Precompute values for polygon creation
    rad = std::hypot(width, height) / 2;
    alpha = std::atan2(width, height);

    createPolygon(); // Create the initial polygon
}

void Car::update(const std::vector<std::unique_ptr<Car>>& traffic, Server& server) {
    if (!damaged) {
        controls.update(); 
        move();
        createPolygon();
        assessDamage(traffic);
    }

    if (sensor) {
        sensor->update(borders, traffic);
    }

    // function to send data to server
    if (controlsType == "AI" && !damaged) {
        sendData(server);
        receiveData(server);
    }
}

void Car::assessDamage(const std::vector<std::unique_ptr<Car>>& traffic) {
    for (const auto& border : borders) {
        if (Utils::polysIntersect(polygon, {border.first, border.second})) {
            std::cout << "Collision detected!" << std::endl;
            damaged = true;   
            return; 
        }
    }

    for (const auto& carPtr : traffic) {
        if (carPtr && Utils::polysIntersect(polygon, carPtr->polygon)) {
            std::cout << "Collision detected!" << std::endl;
            damaged = true;   
            return; 
        }
    }

    damaged = false;
}


void Car::createPolygon() {
    polygon.clear(); 

    // float angles[4] = {
    //     angle - alpha,
    //     angle + alpha,
    //     M_PI + angle - alpha,
    //     M_PI + angle + alpha
    // };

    float angles[4] = {
        static_cast<float>(angle - alpha),
        static_cast<float>(angle + alpha),
        static_cast<float>(M_PI + angle - alpha),
        static_cast<float>(M_PI + angle + alpha)
    };



    for (int i = 0; i < 4; ++i) {
        polygon.push_back(sf::Vector2f(
            x - std::sin(angles[i]) * rad, 
            y - std::cos(angles[i]) * rad
        ));
        polygonShape.setPoint(i, polygon[i]);
    }
}

void Car::move() {
    // Update speed
    if (controls.forward) {
        speed += acceleration;
    } else if (controls.reverse) {
        speed -= acceleration;
    } else {
        if (speed > 0) {
            speed -= friction;
        } else if (speed < 0) {
            speed += friction;
        }
        if (std::abs(speed) < friction) {
            speed = 0;
        }
    }
    speed = std::clamp(speed, -maxSpeed / 2.0f, maxSpeed);

    // Update angle
    if (speed != 0) {
        float flip = speed > 0 ? 1 : -1;
        float turningRate = 0.01 * std::abs(speed);
        if (controls.left) {
            angle += turningRate * flip;
        } else if (controls.right) {
            angle -= turningRate * flip;
        }
    }

    // Update position
    x -= std::sin(angle) * speed;
    y -= std::cos(angle) * speed;
}

void Car::draw(sf::RenderWindow& window, const std::string& color, bool isFocused) {
    
    sf::Color fillColor;
    if (damaged) {
        fillColor = sf::Color(190, 190, 190);
    } else {
        if (color == "red") {
            fillColor = sf::Color::Red;
        } else if (color == "blue") {
            fillColor = sf::Color::Blue;
            if (!isFocused) {
                fillColor.a = 51;  // Set alpha to 51 (20% transparency) for non-focused blue cars
            }
        }
    }

    if (polygonShape.getFillColor() != fillColor) {
        polygonShape.setFillColor(fillColor);
    }

    window.draw(polygonShape);
    if (sensor) {
        sensor->draw(window);
    }
}



void Car::sendData(Server& server) {

    nlohmann::json data;

    // Add car's basic information
    data["id"] = id;
    data["position"] = {x, y};
    data["speed"] = speed;
    data["angle"] = angle;
    data["damaged"] = damaged;

    // Add car's polygon points
    std::vector<nlohmann::json> polygonPoints;
    for (const auto& point : polygon) {
        polygonPoints.push_back({{"x", point.x}, {"y", point.y}});
    }
    data["polygon_points"] = polygonPoints;

    // Add sensor data if available
    if (sensor != nullptr) {
        std::vector<nlohmann::json> sensorReadings;
        for (const auto& offset : sensor->offsets) {
            // Check if the offset is NaN and make it zero if it is
            if (std::isnan(offset)) {
                sensorReadings.push_back(0);
            } else {
                // Assuming the offset is a float value, add it directly to sensorReadings
                sensorReadings.push_back(1-offset);
            }
        }
        data["sensor_readings"] = sensorReadings;
    }

    // Convert JSON object to string
    std::string dataStr = data.dump();

    // Send serialized data through the server
    server.sendData(dataStr.c_str());

}

void Car::receiveData(Server& server) {

    // Receive data from the server
    std::string dataStr = server.receiveData();

    // Parse the data into a JSON object
    nlohmann::json data = nlohmann::json::parse(dataStr);

    int receivedId = data["id"];
    if (receivedId != this->id) {
        // If the ID does not match, ignore the controls update
        return;
    }

    // Update the car's controls
    controls.forward = data["controls"]["forward"] == 1;
    controls.reverse = data["controls"]["reverse"] == 1;
    controls.left = data["controls"]["left"] == 1;
    controls.right = data["controls"]["right"] == 1;

    
}

void Car::resetGameState(float x, float y, float width, float height, float roadLeft, float roadRight)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->roadLeft = roadLeft;
    this->roadRight = roadRight;
    this->speed = 0;
    this->angle = 0;
    this->damaged = false;
    this->createPolygon();
}