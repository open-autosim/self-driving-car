#include <SFML/Graphics.hpp>
#include "car.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Car Simulation");

    // Create a Car object
    Car car(400, 300, 50, 100); // Adjust the position and size as needed

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the car's state
        car.update(window);

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw the car
        car.draw(window);

        // Finally, display the rendered frame on screen
        window.display();
    }

    return 0;
}
