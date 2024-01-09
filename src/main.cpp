#include <SFML/Graphics.hpp>
#include "car.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Car Simulation");
    window.setFramerateLimit(60);
    sf::Color lightGray(192, 192, 192);

    // Create a Car object
    Car car(1280/2, 720/2, 50, 100); // Adjust the position and size as needed

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

        // Draw the car
        car.draw(window);

        // Finally, display the rendered frame on screen
        window.display();
    }

    return 0;
}
