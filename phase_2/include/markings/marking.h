#ifndef MARKING_H
#define MARKING_H

#include <SFML/Graphics.hpp>
#include "primitives/point.h"
#include "primitives/segment.h"
#include "primitives/envelope.h"
#include "primitives/polygon.h"
#include "math/utils.h" 

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>

class Marking {
public: 

    //default constructor
    Marking() {}

    Marking(const Point& center, const Point& directionVector, int width, int height)
        : center(center), directionVector(directionVector), width(width), height(height) 
    {
        std::shared_ptr<Point> p1 = std::make_shared<Point>(Utils::translate(center, Utils::angle(directionVector), height/2));
        std::shared_ptr<Point> p2 = std::make_shared<Point>(Utils::translate(center, Utils::angle(directionVector), -height/2));
        support = Segment(p1, p2);
        poly = Envelope(support, width, 0).polygon;
    }

    virtual void draw(sf::RenderWindow& window) const {
        poly.draw(window);
    }

    virtual std::string getType() const = 0;

    // get polygon
    Polygon getPolygon() const { return poly; }

    //get center
    Point getCenter() const { return center; }

    
    template<class Archive>
    void serialize(Archive& archive) {
        archive(center, directionVector, width, height, support, poly); // Serialize all relevant members
    }


protected:
    Point center;
    Point directionVector;
    int width;
    int height;
    Segment support;
    Polygon poly;
};


CEREAL_REGISTER_TYPE(Marking);


#endif // MARKING_H
