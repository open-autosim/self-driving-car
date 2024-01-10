#include <SFML/Graphics.hpp>
#include "car.h"
#include "road.h"

int main() {

    int width = 600;
    int height = 800;

    sf::RenderWindow window(sf::VideoMode(width, height), "Self Driving Car");
    window.setFramerateLimit(60);

    // Create a Car object
    Road road(width/2, 300, 3); // Adjust the position and width as needed
    Car car(road.getLaneCenter(1), height/2, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "KEYS"); // Adjust the position and size as needed
    std::vector<Car> traffic = { Car(road.getLaneCenter(1), height/2-400, 50, 100, road.getLeft(), road.getRight(), road.getBorders(), "DUMMY", 2) };

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
            car.update(std::vector<Car> {});
        }

        // Update the car's state
        car.update(traffic);

        // Update the view to follow the car
        float verticalOffset = height * 0.2; // Adjust this value as needed
        view.setCenter(width / 2, car.getY() - verticalOffset);

        window.clear(sf::Color(192, 192, 192));

        // Apply the view
        window.setView(view);

        // Draw the road and car
        road.draw(window);
        for (auto& car : traffic) {
            car.draw(window, "red");
        }
        car.draw(window, "blue");

        // Finally, display the rendered frame on screen
        window.display();
    }

    return 0;
}
