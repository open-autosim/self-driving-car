#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include <SFML/Graphics.hpp>
#include <memory> // For std::shared_ptr
#include "math/graph.h"
#include "math/utils.h"

class GraphEditor {
public:
    GraphEditor(sf::RenderWindow& window, sf::RectangleShape& context, Graph& graph);

    void handleEvent(const sf::Event& event);
    void update();
    void display();
    void print();

private:
    sf::RenderWindow& window;
    sf::RectangleShape& context;
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
