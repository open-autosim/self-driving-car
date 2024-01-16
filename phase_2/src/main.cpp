#include <SFML/Graphics.hpp>
#include <iostream>
#include "math/graph.h"
#include <cstdlib>
#include <ctime>
#include "utils/button.h"
#include "graph_editor.h"
#include "viewport.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>

#include "imgui.h"
// #include "imgui_stdlib.h"
#include "imgui-sfml/imgui-SFML.h"

void saveGraph(const Graph& graph, const std::string& filename) {
    std::ofstream os(filename, std::ios::binary);
    cereal::BinaryOutputArchive archive(os);
    archive(graph);
    std::cout << "Graph saved to " << filename << std::endl;
}

bool loadGraph(Graph& graph, const std::string& filename) {
    std::ifstream is(filename, std::ios::binary);
    if (!is) {
        std::cout << "File not found: " << filename << std::endl;
        return false; // File not found
    }
    cereal::BinaryInputArchive archive(is);
    archive(graph);
    return true;
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

    // auto p1 = std::make_shared<Point>(500, 500);
    // auto p2 = std::make_shared<Point>(800, 400);
    // auto p3 = std::make_shared<Point>(300, 300);
    // auto p4 = std::make_shared<Point>(600, 700);

    //load graph info from file
    Graph graph;
    if (!loadGraph(graph, "graph_data.bin")) {
        std::cout << "No saved graph found, starting with a new graph." << std::endl;
    }
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
            saveGraph(graph, "graph_data.bin");
        }
        if (ImGui::Button("Dispose")) {
            graphEditor.dispose();
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

