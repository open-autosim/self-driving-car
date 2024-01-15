#include <SFML/Graphics.hpp>
#include <iostream>
#include "math/graph.h"
#include <cstdlib>
#include <ctime>
#include "utils/button.h"
#include "graph_editor.h"


int main() {
    int windowWidth = 1200;
    int windowHeight = 1200;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "World Editor");

    // Proportions and margins
    float contextMargin = 50;
    float contextSize = windowWidth - 2 * contextMargin;
    float buttonWidth = 150;
    float buttonHeight = 30;
    float buttonSpacing = 10;
    float buttonYPosition = contextMargin + contextSize + 10;

    sf::RectangleShape context(sf::Vector2f(contextSize, contextSize));
    context.setFillColor(sf::Color(42, 170, 85));
    context.setPosition(contextMargin, contextMargin);

    auto p1 = std::make_shared<Point>(500, 500);
    auto p2 = std::make_shared<Point>(800, 400);
    auto p3 = std::make_shared<Point>(300, 300);
    auto p4 = std::make_shared<Point>(600, 700);

    // Create Segments with shared pointers
    Segment s1(p1, p2);
    Segment s2(p2, p3);
    Segment s3(p3, p4);
    Segment s4(p4, p1);

    // Create Graph with vector of shared pointers to Points and Segments
    Graph graph({p1, p2, p3, p4}, {s1, s2, s3, s4});

    // Initialize GraphEditor with Graph
    GraphEditor graphEditor(window, context, graph);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            graphEditor.handleEvent(event);
            
        }

        graphEditor.update();

        window.clear();

        graphEditor.display();
    }

    return 0;
}

