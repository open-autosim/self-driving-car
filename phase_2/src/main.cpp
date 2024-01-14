#include <SFML/Graphics.hpp>
#include <iostream>
#include "math/graph.h"
#include <cstdlib>
#include <ctime>
#include "utils/button.h"


int main() {
    int windowWidth = 1200;
    int windowHeight = 1200;

    sf::Font font;
    if (!font.loadFromFile("assets/Roboto-Regular.ttf")) {
        // Handle error - for example, print an error message and exit
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

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

    // Sample points and segments
    Point p1(500, 500), p2(800, 400), p3(300, 300), p4(600, 700);
    Segment s1(p1, p2), s2(p1, p3), s3(p1, p4), s4(p2, p3);
    Graph graph({p1, p2, p3, p4}, {s1, s2, s3, s4});


    std::srand(std::time(nullptr));

    // Create Button instances
    Button addPointButton(contextMargin, buttonYPosition, buttonWidth, buttonHeight, "Add Point", font, sf::Color(128, 128, 128), sf::Color(170, 170, 170), sf::Color(100, 100, 100));
    Button addSegmentButton(contextMargin + buttonWidth + buttonSpacing, buttonYPosition, buttonWidth, buttonHeight, "Add Segment", font, sf::Color(128, 128, 128), sf::Color(170, 170, 170), sf::Color(100, 100, 100));
    Button removeSegmentButton(contextMargin + 2 * (buttonWidth + buttonSpacing), buttonYPosition, buttonWidth, buttonHeight, "Remove Segment", font, sf::Color(128, 128, 128), sf::Color(170, 170, 170), sf::Color(100, 100, 100));
    Button removePointButton(contextMargin + 3 * (buttonWidth + buttonSpacing), buttonYPosition, buttonWidth, buttonHeight, "Remove Point", font, sf::Color(128, 128, 128), sf::Color(170, 170, 170), sf::Color(100, 100, 100));
    Button disposeButton(contextMargin + 4 * (buttonWidth + buttonSpacing), buttonYPosition, buttonWidth, buttonHeight, "Dispose", font, sf::Color(128, 128, 128), sf::Color(170, 170, 170), sf::Color(100, 100, 100));

    // Set callbacks for buttons
    addPointButton.setOnClick([&]() {
        // Action for addPointButton
        int randX = std::rand() % (int)(context.getSize().x) + (int)context.getPosition().x;
        int randY = std::rand() % (int)(context.getSize().y) + (int)context.getPosition().y;
        Point newPoint(randX, randY);
        graph.tryAddPoint(newPoint);
    });

    addSegmentButton.setOnClick([&]() {
        // Action for addSegmentButton
        int index1 = std::rand() % graph.getPoints().size();
        int index2 = std::rand() % graph.getPoints().size();
        bool success = graph.tryAddSegment(
            Segment(graph.getPoints()[index1], graph.getPoints()[index2]));        
    });

    removeSegmentButton.setOnClick([&]() {
        // Action for removeSegmentButton
        if (graph.getSegments().size() == 0) {
            //print error message
            std::cout << "No segments to remove" << std::endl;
            return;
        }
        int index = std::rand() % graph.getSegments().size();
        graph.removeSegment(graph.getSegments()[index]);

    });

    removePointButton.setOnClick([&]() {
        // Action for removePointButton
        if (graph.getPoints().size() == 0) {
            //print error message
            std::cout << "No points to remove" << std::endl;
            return;
        }
        int index = std::rand() % graph.getPoints().size();
        graph.removePoint(graph.getPoints()[index]);
    });

    disposeButton.setOnClick([&]() {
        graph.dispose();
    });


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            // Handle events for buttons
            addPointButton.handleEvent(event, window);
            addSegmentButton.handleEvent(event, window);
            removeSegmentButton.handleEvent(event, window);
            removePointButton.handleEvent(event, window);
            disposeButton.handleEvent(event, window);
        }

        // Clear the window
        window.clear();

        // Draw the green rectangle as the context
        window.draw(context);

        // Draw the graph within the context
        graph.draw(window);

        // Draw buttons
        addPointButton.draw(window);
        addSegmentButton.draw(window);
        removeSegmentButton.draw(window);
        removePointButton.draw(window);
        disposeButton.draw(window);

        // Display the window
        window.display();
    }

    return 0;
}

// int main() {

//     int width = 600;
//     int height = 600;

//     sf::RenderWindow window(sf::VideoMode(width, height), "World Editor");

//     sf::RectangleShape context;
//     context.setSize(sf::Vector2f(500, 500));
//     context.setFillColor(sf::Color(42, 170, 85));
//     context.setPosition(50, 50);

//     std::srand(std::time(nullptr));
//     // Define a button
//     sf::RectangleShape button(sf::Vector2f(100, 50));
//     // Calculate the position to center the button under the context
//     float buttonX = context.getPosition().x + (context.getSize().x / 2) - (button.getSize().x / 2);
//     float buttonY = context.getPosition().y + context.getSize().y + 10; // 10 pixels below the context
//     button.setPosition(buttonX, buttonY);
//     // button.setFillColor(sf::Color(128, 128, 128)); // Grey color
//     sf::Color normalColor = sf::Color(128, 128, 128); // Grey color
//     sf::Color hoverColor = sf::Color(170, 170, 170); // Lighter Grey
//     sf::Color clickColor = sf::Color(100, 100, 100); // Darker Grey
//     button.setFillColor(normalColor);



//     // Sample points and segments
//     Point p1(200, 200), p2(500, 200), p3(400, 400), p4(100, 300);
//     Segment s1(p1, p2), s2(p1, p3), s3(p1, p4), s4(p2, p3);
//     Graph graph({p1, p2, p3, p4}, {s1, s2, s3, s4});
    

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();

//             // key escape pressed
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//                 window.close();

//             if (event.type == sf::Event::MouseButtonPressed) {
//                 if (event.mouseButton.button == sf::Mouse::Left) {
//                     sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//                     sf::Vector2f buttonPos = button.getPosition();
//                     sf::Vector2f buttonSize = button.getSize();

//                     // Check if the click was within the button's bounds
//                     if (mousePos.x >= buttonPos.x && mousePos.x <= (buttonPos.x + buttonSize.x) &&
//                         mousePos.y >= buttonPos.y && mousePos.y <= (buttonPos.y + buttonSize.y)) {
                        
                        
//                             // Generate a random point within the context bounds
//                             int randX = std::rand() % (int)(context.getSize().x) + (int)context.getPosition().x;
//                             int randY = std::rand() % (int)(context.getSize().y) + (int)context.getPosition().y;
//                             Point newPoint(randX, randY);

//                             //print the new point
//                             std::cout << "New Point: " << newPoint.x << ", " << newPoint.y << std::endl;

//                             // Add the new point to the graph
//                             bool added = graph.tryAddPoint(newPoint);
//                             // print added true or false
//                             std::cout << "Added: " << std::boolalpha << added << std::endl;
//                     }
//                 }
//             }


//         }

//         // Clear the window
//         window.clear();

//         // Draw the green rectangle as the context
//         window.draw(context);

//         // Draw the graph within the context
//         graph.draw(window);
 
//         window.draw(button);

//         // Display the window
//         window.display();
//     }

//     return 0;
// }