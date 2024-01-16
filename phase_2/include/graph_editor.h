#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include <SFML/Graphics.hpp>
#include <memory> // For std::shared_ptr
#include "math/graph.h"
#include "math/utils.h"
#include "viewport.h"

class GraphEditor {
public:
    GraphEditor(Viewport& viewport, Graph& graph);

    void handleEvent(const sf::Event& event);
    void display();
    void print();
    void dispose();

private:

    Viewport& viewport;
    sf::RenderWindow& window;
    Graph& graph;

    std::shared_ptr<Point> selected;
    std::shared_ptr<Point> hovered;
    bool dragging;
    sf::Vector2i mouse;

    void handleMouseMove(const sf::Event& event);
    void handleMouseDown(const sf::Event& event);
    void select(std::shared_ptr<Point> point);
    void removePoint(std::shared_ptr<Point> point);
};

#endif // GRAPH_EDITOR_H
