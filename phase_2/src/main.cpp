#include <SFML/Graphics.hpp>
#include <iostream>
#include "math/graph.h"
#include <cstdlib>
#include <ctime>
#include "utils/button.h"
#include "graph_editor.h"
#include "viewport.h"

#include "imgui.h"
// #include "imgui_stdlib.h"
#include "imgui-SFML/imgui-SFML.h"

void save() {
    std::cout << "Save button pressed!" << std::endl;
}

void dispose() {
    std::cout << "Dispose button pressed!" << std::endl;
}


int main() {
    int windowWidth = 1200;
    int windowHeight = 1200;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "World Editor");    
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);


    // Proportions and margins
    float buttonWidth = 150;
    float buttonHeight = 30;
    float buttonSpacing = 10;
    float buttonYPosition = 10;

    auto p1 = std::make_shared<Point>(500, 500);
    auto p2 = std::make_shared<Point>(800, 400);
    auto p3 = std::make_shared<Point>(300, 300);
    auto p4 = std::make_shared<Point>(600, 700);
    Segment s1(p1, p2);
    Segment s2(p2, p3);
    Segment s3(p3, p4);
    Segment s4(p4, p1);
    Graph graph({p1, p2, p3, p4}, {s1, s2, s3, s4});
    Viewport viewport(window);
    GraphEditor graphEditor(viewport, graph);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            // Only process viewport and editor events if ImGui does not want to capture the mouse
            if (!ImGui::GetIO().WantCaptureMouse) {
                if (event.type == sf::Event::MouseButtonPressed ||
                    event.type == sf::Event::MouseButtonReleased ||
                    event.type == sf::Event::MouseMoved) {
                    viewport.handleEvent(event);
                    graphEditor.handleEvent(event);
                }
            }

            // Process other events normally
            if (event.type == sf::Event::MouseWheelScrolled) {
                viewport.handleEvent(event);
             }
            
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // ImGui window
        ImGui::Begin("Control Panel");
        if (ImGui::Button("Save")) {
            save();
        }
        if (ImGui::Button("Dispose")) {
            dispose();
        }
        ImGui::End();


        window.clear(sf::Color(42, 170, 85));

        viewport.reset();
        graphEditor.display();

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}

