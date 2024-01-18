#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <SFML/Graphics.hpp>
#include "primitives/point.h"
#include "math/utils.h"

class Viewport {
public:
    Viewport(sf::RenderWindow& window);

    void reset();
    Point getMouse(const sf::Event& event, bool subtractDragOffset = false);
    // Point getOffset() const;
    void handleEvent(const sf::Event& event);

    float getZoom() const { return zoom; }
    sf::RenderWindow& getWindow() const { return window; }

    Point getOffset() const;

    //set zoom
    void setZoom(float zoom) { this->zoom = zoom; }
    void setOffset(Point offset) { this->offset = offset; }
    
private:

    sf::RenderWindow& window;
    float zoom;
    Point center;
    Point offset;
    struct Drag {
        Point start;
        Point end;
        Point offset;
        bool active;
    } drag;

    float scrollAccumulator = 0.0f;
    const float scrollThreshold = 5.0f;

    void handleMouseWheel(const sf::Event& event);
    void handleMouseDown(const sf::Event& event);
    void handleMouseMove(const sf::Event& event);
    void handleMouseUp(const sf::Event& event);
};

#endif // VIEWPORT_H
