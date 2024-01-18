#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <SFML/Graphics.hpp>
#include "primitives/point.h"

class DrawableObject {
public:
    virtual ~DrawableObject() {}

    // Pure virtual function for drawing the object.
    virtual void draw(sf::RenderWindow& window, const Point& viewPoint) const = 0;

    // Virtual function for calculating distance to a point.
    virtual float distanceToPoint(const Point& point) const = 0;
};

#endif // DRAWABLE_OBJECT_H
