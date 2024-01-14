#include <SFML/Graphics.hpp>
#include "graph.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 1200), "World Editor");

    // Sample points and segments
    Point p1(200, 200), p2(500, 200), p3(400, 400), p4(100, 300);
    Segment s1(p1, p2), s2(p1, p3), s3(p1, p4), s4(p2, p3);
    Graph graph({p1, p2, p3, p4}, {s1, s2, s3, s4});

    while (window.isOpen()) {
       
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            window.close();

            // key escape pressed
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();
        }

        window.clear();
        graph.draw(window);
        window.display();
    }
    return 0;   
}