#include <SFML/Graphics.hpp>
#include "car.h"
#include "road.h"

int main() {

    int width = 1280;
    int height = 1000;

    sf::RenderWindow window(sf::VideoMode(width, height), "Car Simulation");
    window.setFramerateLimit(60);

    // Create a Car object
    Road road(width/2, height/3); // Adjust the position and width as needed
    Car car(road.getLaneCenter(0), height/2, 50, 100, road.getLeft(), road.getRight()); // Adjust the position and size as needed

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

        // Update the car's state
        car.update();

        // Update the view to follow the car
        float verticalOffset = height * 0.2; // Adjust this value as needed
        view.setCenter(width / 2, car.getY() - verticalOffset);

        window.clear(sf::Color(192, 192, 192));

        // Apply the view
        window.setView(view);

        // Draw the road and car
        road.draw(window);
        car.draw(window);

        // Finally, display the rendered frame on screen
        window.display();
    }

    return 0;
}
