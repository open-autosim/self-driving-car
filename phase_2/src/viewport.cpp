#include "viewport.h"
#include <iostream>
#include <cmath> // for std::signbit
#include <algorithm> // Include the <algorithm> header for std::max

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
    } 
}

Point Viewport::getMouse(const sf::Event& event, bool subtractDragOffset) {

    sf::Vector2f worldMouse = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
    Point p(worldMouse.x, worldMouse.y);
   
    if (subtractDragOffset) {
        p = Utils::subtract(p, drag.offset);
    }
    return p;
}


Point Viewport::getOffset() const {
    return Utils::add(offset, drag.offset);
}


void Viewport::reset() {
    sf::View view = window.getDefaultView();
    view.setCenter(center.x, center.y);
    view.zoom(zoom);
    window.setView(view);

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
        
        Point currentMouse(event.mouseMove.x, event.mouseMove.y);
        Point movement = Utils::subtract(currentMouse, drag.start);
        movement = Utils::scale(movement, zoom);
        drag.offset = Utils::add(drag.offset, movement);
        // Update the center position
        center = Utils::subtract(center, movement);
        drag.start = currentMouse;
    }
}

void Viewport::handleMouseUp(const sf::Event& event) {
    if (drag.active) { 
        
        offset = Utils::add(offset, drag.offset);
        drag = {Point(0, 0), Point(0, 0), Point(0, 0), false};    
    }
}

void Viewport::handleMouseWheel(const sf::Event& event) {
    
    float zoomStep = 0.1f;
    if (event.mouseWheelScroll.delta < 0) {
        zoom += zoomStep;
    } else if (event.mouseWheelScroll.delta > 0) {
        zoom -= zoomStep;
    }
    zoom = std::max(1.0f, std::min(5.0f, zoom));
}

