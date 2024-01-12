#include <SFML/Graphics.hpp>
#include "car.h"
#include "road.h"
#include "server.h"
#include <iostream>

void resetGameState(Road& road, Car& car, std::vector<Car>& traffic, sf::View& view) {
 
    int width = 600;
    int height = 800;


    car.resetGameState(road.getLaneCenter(1), height/2, 50, 100, road.getLeft(), road.getRight());

    // Reset each traffic car
    int trafficInitialY[] = {height/2-300, height/2-600, height/2-600, height/2-900, height/2-900, height/2-1200, height/2-1200};
    int laneIndex[] = {1, 0, 2, 0, 1, 2, 1}; // Corresponding lane indexes

    for (size_t i = 0; i < traffic.size(); ++i) {
        traffic[i].resetGameState(traffic[i].getX(), trafficInitialY[i], 50, 100, road.getLeft(), road.getRight()); // Reset with initial Y position, angle, and speed
    }

}

std::vector<std::unique_ptr<Car>> generateCars(int N, Road& road, int height, bool isTraffic = false) 
{
    std::vector<std::unique_ptr<Car>> cars;
    cars.reserve(N);

    if (!isTraffic) {
        // Generate AI cars
        for (int i = 0; i < N; i++) {
            cars.push_back(std::make_unique<Car>(road.getLaneCenter(1), height/2, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "AI"));
        }
    } else {
        // Generate traffic cars with fixed spacing, max 2 cars per y-height block, and first car 400 units away
        int numLanes = road.getLaneCount();
        int spacing = 300; 
        int initialYOffset = 400; // Offset for the first traffic car
        int laneAllocation = 0;

        for (int i = 0; i < N; i++) {
            int yPos = height/2 - initialYOffset - (i / 2) * spacing; // Adjust initial position
            int lane = laneAllocation % numLanes;
            
            cars.push_back(std::make_unique<Car>(road.getLaneCenter(lane), yPos, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2));

            laneAllocation++;
            if (laneAllocation % numLanes == 0) {
                // After assigning a car to each lane, move to the next y-height block
                laneAllocation += numLanes;
            }
        }
    }
    return cars;
}



// std::vector<std::unique_ptr<Car>> generateCars(int N, Road& road, int height, bool isTraffic = false) 
// {
//     std::vector<std::unique_ptr<Car>> cars;
//     cars.reserve(N);

//     if (!isTraffic) {
//         // Generate AI cars
//         for (int i = 0; i < N; i++) {
//             cars.push_back(std::make_unique<Car>(road.getLaneCenter(1), height/2, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "AI"));
//         }
//     } else {
//         // Generate traffic cars with varying positions
//         int trafficInitialY[] = {height/2-300, height/2-600, height/2-600, height/2-900, height/2-900, height/2-1200, height/2-1200};
//         int laneIndex[] = {1, 0, 2, 0, 1, 2, 1}; // Corresponding lane indexes

//         for (int i = 0; i < N; i++) {
//             int lane = laneIndex[i % 7]; // Loop through lane indexes
//             cars.push_back(std::make_unique<Car>(road.getLaneCenter(lane), trafficInitialY[i % 7], 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2));
//         }
//     }
//     return cars;
// }


int main() {

    Server server(8080);
    server.initServer();
    server.waitForConnection();



    int width = 600;
    int height = 800;

    sf::RenderWindow window(sf::VideoMode(width, height), "Self Driving Car");
    window.setFramerateLimit(60);

    // Create a Car object
    Road road(width/2, 300, 3); // Adjust the position and width as needed
    std::vector<std::unique_ptr<Car>> cars = generateCars(100, road, height);

    std::vector<std::unique_ptr<Car>> traffic = generateCars(50, road, height, true);

    // Create a view (camera)
    sf::View view(sf::FloatRect(0, 0, width, height));

    while (window.isOpen()) {
        
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

    
        std::vector<std::unique_ptr<Car>> emptyTraffic; // An empty vector of unique_ptr<Car>
        for (auto& car : traffic) {
            if (car) {
                car->update(emptyTraffic, server);
            }
        }

        for (auto& car : cars) {
            if (car) {
                car->update(traffic, server);
            }
         }

        float lowestY = std::numeric_limits<float>::max();
        sf::Vector2f center;
        for (auto& car : cars) {
            if (car && car->getY() < lowestY) {
                lowestY = car->getY();
                center = sf::Vector2f(width / 2, car->getY() - height * 0.2f);
            }
        }

        if (lowestY != std::numeric_limits<float>::max()) {
            view.setCenter(center);
        }

        window.clear(sf::Color(192, 192, 192));
        window.setView(view);
        road.draw(window);

        for (auto& car : traffic) {
            car->draw(window, "red");
        }

        for (auto& car : cars) {
            car->draw(window, "blue");
        }

        for (size_t i = 0; i < cars.size(); ++i) {
            if (cars[i]) {
                bool isFocused = (cars[i]->getY() == lowestY);  // Check if this car is the currently focused car
                bool drawSensor = isFocused;
                cars[i]->draw(window, "blue", isFocused, drawSensor);  // Pass the "isFocused" parameter
            }
        }

        window.display();

    }

    server.closeServer();
    return 0;
    
    

}

