#include "viewport.h"
#include <iostream>
#include <cmath> // for std::signbit

Viewport::Viewport(sf::RenderWindow& window) 
        : window(window), zoom(1), center(window.getSize().x / 2, window.getSize().y / 2), 
            offset(Utils::scale(center, -1)), drag({Point(0, 0), Point(0, 0), Point(0, 0), false}) {}


void Viewport::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        handleMouseWheel(event);
    } else if (event.type == sf::Event::MouseButtonPressed) {
        handleMouseDown(event);
    } else if (event.type == sf::Event::MouseButtonReleased) {
        handleMouseUp(event);
    } else if (event.type == sf::Event::MouseMoved) {
        handleMouseMove(event);
    } else if (event.type == sf::Event::Resized) {
    
    }
}

void Viewport::handleMouseWheel(const sf::Event& event) {
    // Accumulate the delta values
    #include <algorithm> // Include the <algorithm> header for std::max

    scrollAccumulator += event.mouseWheelScroll.delta;

    // Check if the accumulated value has reached the threshold
    if (std::abs(scrollAccumulator) >= scrollThreshold) {
        int sign = scrollAccumulator > 0 ? -1 : 1;
        scrollAccumulator = 0.0f;

        float step = 0.1f;
        zoom += sign * step;
        zoom = std::max(1.0f, std::min(5.0f, zoom)); 
        
    }
}

sf::Vector2i Viewport::getMouse(const sf::Event& event, bool subtractDragOffset) {
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    sf::Vector2f worldMouse = window.mapPixelToCoords(mouse);

    return sf::Vector2i(worldMouse);
}

void Viewport::handleMouseDown(const sf::Event& event) {

    // check if middle mouse button is pressed
    if (event.mouseButton.button == sf::Mouse::Middle) {
        // set drag start position
        drag.start = Point(event.mouseButton.x, event.mouseButton.y);    
        drag.active = true;
    }    
}

void Viewport::handleMouseMove(const sf::Event& event) {
    
    if (drag.active) {

        drag.end = Point(event.mouseMove.x, event.mouseMove.y);
        drag.offset = Utils::subtract(drag.end, drag.start);
        drag.offset = Utils::scale(drag.offset, zoom);
        center = Utils::subtract(center, drag.offset);
        drag.start = drag.end;
    }
}

void Viewport::handleMouseUp(const sf::Event& event) {
    
    if (drag.active) { 
        offset = Utils::add(offset, drag.offset);
        //reset drag
        drag.active = false;
        drag.start = Point(0, 0);
        drag.end = Point(0, 0);
        drag.offset = Point(0, 0);
    }
}

void Viewport::reset() {
    sf::View view = window.getDefaultView();
    view.zoom(zoom);
    view.setCenter(center.x, center.y);
    window.setView(view);
}