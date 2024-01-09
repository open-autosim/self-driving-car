#include <SFML/Graphics.hpp>
#include "car.h"
#include "road.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 1000), "Car Simulation");
    window.setFramerateLimit(60);
    sf::Color lightGray(192, 192, 192);

    // Create a Car object
    Road road(1280/2, 500); // Adjust the position and width as needed
    Car car(1280/2, 1000/2, 50, 100, road.getLeft(), road.getRight()); // Adjust the position and size as needed

    while (window.isOpen()) {
        
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear(lightGray);

        // Update the car's state
        car.update();

        // Draw the road
        road.draw(window);

        // Draw the car
        car.draw(window);

        // Finally, display the rendered frame on screen
        window.display();
    }

    return 0;
}
