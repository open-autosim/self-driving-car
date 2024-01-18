// GraphEditor.cpp
#include <iostream>
#include "editors/graph_editor.h"



GraphEditor::GraphEditor(World& world, Viewport& viewport, Graph& graph)
    : world(world), mouseEnabled(true), viewport(viewport), graph(graph), selected(nullptr), hovered(nullptr), dragging(false), window(viewport.getWindow()) {}


void GraphEditor::enable() {
    mouseEnabled = true;
}

void GraphEditor::disable() {
    mouseEnabled = false;
}

void GraphEditor::handleEvent(const sf::Event& event) {

    if (!mouseEnabled) {
        selected = nullptr;
        hovered = nullptr;
        return;
    }
    
    if (event.type == sf::Event::MouseMoved) {
        handleMouseMove(event);
    } else if (event.type == sf::Event::MouseButtonPressed) {
        handleMouseDown(event);
    } else if (event.type == sf::Event::MouseButtonReleased) {
        dragging = false;
    }
}

void GraphEditor::handleMouseMove(const sf::Event& event) {
    // mouse = sf::Mouse::getPosition(window);

    Point p = viewport.getMouse(event, true);
    mouse = sf::Vector2i(p.x, p.y);
    hovered = Utils::getNearestPoint(Point(mouse.x, mouse.y), graph.getPoints(), 10*viewport.getZoom());
    if (dragging && selected) {
        selected->x = mouse.x;
        selected->y = mouse.y;
    }
}

void GraphEditor::handleMouseDown(const sf::Event& event) {
    
    if (event.mouseButton.button == sf::Mouse::Right) {
        
        if (selected) {
            selected = nullptr;
        } else if (hovered) {
            removePoint(hovered);
        }
    }
    
    if (event.mouseButton.button == sf::Mouse::Left) {
        if (hovered) {
            select(hovered);
            dragging = true;
            return;
        }
        Point mousePoint(mouse.x, mouse.y);
        graph.addPoint(mousePoint);
        select(graph.getPoint(mousePoint));
        hovered = selected;
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

    if (!mouseEnabled) return;

    graph.draw(window);

    if (hovered) {
        hovered->draw(window, 18, sf::Color::Black, false, true);
    }

    if (selected) {
        Point intent = hovered ? *hovered : Point(mouse.x, mouse.y);
        Segment(selected, std::make_shared<Point>(intent)).draw(window, 2, sf::Color::Black, true);
        selected->draw(window, 18, sf::Color::Black, true, false);
    }
}

void GraphEditor::dispose() {

    //clear points and segments
    graph.dispose();
    //clear selected and hovered
    selected = nullptr;
    hovered = nullptr;

    world.clearWorld();
}