// GraphEditor.cpp
#include <iostream>
#include "graph_editor.h"



GraphEditor::GraphEditor(sf::RenderWindow& window, sf::RectangleShape& context, Graph& graph)
    : window(window), context(context), graph(graph), selected(nullptr), hovered(nullptr), dragging(false) {}

void GraphEditor::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        handleMouseMove(event);
    } else if (event.type == sf::Event::MouseButtonPressed) {
        handleMouseDown(event);
    } else if (event.type == sf::Event::MouseButtonReleased) {
        dragging = false;
    }
}

void GraphEditor::print() {
    std::cout << "Points: " << std::endl;
    for (const auto& point : graph.getPoints()) {
        std::cout << point->x << ", " << point->y << std::endl;
    }
    std::cout << "Segments: " << std::endl;
    for (const auto& segment : graph.getSegments()) {
        std::cout << segment.p1->x << ", " << segment.p1->y << " - " << segment.p2->x << ", " << segment.p2->y << std::endl;
    }
}

void GraphEditor::update() {
    // Update logic, if any
}

void GraphEditor::handleMouseMove(const sf::Event& event) {
    mouse = sf::Mouse::getPosition(window);
    
    hovered = Utils::getNearestPoint(Point(mouse.x, mouse.y), graph.getPoints(), 10);
    if (dragging && selected) {
        selected->x = mouse.x;
        selected->y = mouse.y;
    }
}

void GraphEditor::handleMouseDown(const sf::Event& event) {
    
    if (event.mouseButton.button == sf::Mouse::Left) {
        Point mousePoint(event.mouseButton.x, event.mouseButton.y);
        if (hovered) {
            select(hovered);
            dragging = true;
            return;
        }
        graph.addPoint(mousePoint);
        select(graph.getPoint(mousePoint));
        hovered = selected;
    }

    if (event.mouseButton.button == sf::Mouse::Right) {
        
        if (selected) {
            selected = nullptr;
        } else if (hovered) {
            removePoint(hovered);
        }

    }
        
}

void GraphEditor::select(std::shared_ptr<Point> point) {
    
    if (selected) {
        graph.tryAddSegment(Segment(selected, point));
    }
    selected = point;
}


void GraphEditor::removePoint(std::shared_ptr<Point> point) {
    
    graph.removePoint(*point);
    if (hovered == point) hovered = nullptr;
    if (selected == point) selected = nullptr;

}


void GraphEditor::display() {

    window.draw(context);
    graph.draw(window);


    if (hovered) {
        hovered->draw(window, 18, sf::Color::Black, false, true);
    }

    if (selected) {
    
        Point intent = hovered ? *hovered : Point(mouse.x, mouse.y);
        Segment(selected, std::make_shared<Point>(intent)).draw(window, 2, sf::Color::Black, true);
        selected->draw(window, 18, sf::Color::Black, true, false);
    }

    window.display();
}