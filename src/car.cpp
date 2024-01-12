#include <iostream>
#include "car.h"
#include "utils.h"
#include <cmath>

int Car::nextID = 1;

Car::~Car() {
    delete sensor; // Delete the sensor in the destructor
}

Car::Car(float x, float y, float width, float height, float roadLeft, float roadRight, 
std::vector<std::pair<sf::Vector2f, sf::Vector2f>> borders, std::string controlsType, int maxSpeed, int id)
    : x(x), y(y), width(width), height(height), 
    speed(0), acceleration(0.2), maxSpeed(maxSpeed), 
    friction(0.05), angle(0), 
    roadLeft(roadLeft), roadRight(roadRight), borders(borders), 
    controls(controlsType), controlsType(controlsType),
    sensor(controlsType == "DUMMY" ? nullptr : new Sensor(*this)), id(id) {

    nextID++;
    
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
void Car::update(std::vector<Car> traffic, Server& server) {
    
    if (!damaged) {
        controls.update(); 
        move();
        createPolygon();
        assessDamage(traffic);
    }

    if (sensor != nullptr) {
        sensor->update(borders, traffic);
    }

    // function to send data to server
    if (controlsType == "AI") {
        sendData(server);
        receiveData(server);
    }
}

void Car::assessDamage(std::vector<Car> traffic) {
    
    for (int i = 0; i < borders.size(); i++) { // Ensure we don't go out of bounds
        if (Utils::polysIntersect(polygon, {borders[i].first, borders[i].second})) {
            std::cout << "Collision detected!" << std::endl;
            damaged = true;   
            return; 
        }
    }
    for (int i = 0; i < traffic.size(); i++) { // Ensure we don't hit other cars
        if (Utils::polysIntersect(polygon, traffic[i].polygon)) {
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

void Car::draw(sf::RenderWindow& window, std::string color) {


    if (damaged) {
        polygonShape.setFillColor(sf::Color(190,190,190));
    } else {
        if (color == "red") {
            polygonShape.setFillColor(sf::Color::Red);
        } else if (color == "blue") {
            polygonShape.setFillColor(sf::Color::Blue);
        }
    }

    window.draw(polygonShape);
    if (sensor != nullptr) {
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