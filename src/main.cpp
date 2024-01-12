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

std::vector<Car> generateCars(int N, Road& road, int height) 
{
    std::vector<Car> cars;
    cars.reserve(N); // Reserve memory for N cars
    for (int i = 0; i < N; i++) {
        cars.emplace_back(road.getLaneCenter(1), height/2, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "AI"); 
    }
    return cars;
}


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
    std::vector<Car> cars = generateCars(1, road, height);

    //print cars created
    std::cout << "Cars created: " << cars.size() << std::endl;

    // Car car(road.getLaneCenter(1), height/2, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "AI"); 
    // Car car2(road.getLaneCenter(2), height/2, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "AI");
    std::vector<Car> traffic;
    traffic.reserve(7);

    traffic.emplace_back(road.getLaneCenter(1), height/2-300, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2);
    traffic.emplace_back(road.getLaneCenter(0), height/2-600, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2);
    traffic.emplace_back(road.getLaneCenter(2), height/2-600, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2);
    traffic.emplace_back(road.getLaneCenter(0), height/2-900, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2);
    traffic.emplace_back(road.getLaneCenter(1), height/2-900, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2);
    traffic.emplace_back(road.getLaneCenter(2), height/2-1200, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2);
    traffic.emplace_back(road.getLaneCenter(1), height/2-1200, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2);
    
    std::cout << "Traffic created: " << traffic.size() << std::endl;

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

        for (auto& car : traffic) {
            car.update(std::vector<Car> {}, server);
        }

        std::cout << "Traffic updated" << std::endl;

        if (!cars.empty()) {
            cars[0].update(traffic, server);
            std::cout << "Car 0 updated" << std::endl;

            // Update the view to follow the player car
            float verticalOffset = height * 0.2;
            view.setCenter(width / 2, cars[0].getY() - verticalOffset);
        }
        



        // car.update(traffic, server);

        // if (car.isDamaged()) {
        //     resetGameState(road, car, traffic, view);
        // }

        // Update the view to follow the car
        // float verticalOffset = height * 0.2; // Adjust this value as needed

        // // get the car with the lowest y value
        // Car car = cars[0];
        // view.setCenter(width / 2, car.getY() - verticalOffset);


        window.clear(sf::Color(192, 192, 192));
        window.setView(view);
        road.draw(window);

        for (auto& car : traffic) {
            car.draw(window, "red");
        }
        if (!cars.empty()) {
            cars[0].draw(window, "blue");
        }

        window.display();

    }

    server.closeServer();
    return 0;
    
    

}

