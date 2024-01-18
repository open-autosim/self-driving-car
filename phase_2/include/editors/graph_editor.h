#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include <SFML/Graphics.hpp>
#include <memory> // For std::shared_ptr
#include "math/graph.h"
#include "math/utils.h"
#include "viewport.h"
#include "world.h"

class GraphEditor {
public:
    GraphEditor(World& world, Viewport& viewport, Graph& graph);

    void handleEvent(const sf::Event& event);
    void display();
    void dispose();
    void enable();
    void disable();

    bool isMouseEnabled() const { return mouseEnabled; }

private:

    World& world;
    Viewport& viewport;
    sf::RenderWindow& window;
    Graph& graph;

    bool mouseEnabled;

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
