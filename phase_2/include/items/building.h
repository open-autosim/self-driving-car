#ifndef BUILDING_H
#define BUILDING_H

#include <SFML/Graphics.hpp>
#include "primitives/polygon.h"
#include "primitives/point.h"
#include "math/utils.h"
#include "items/tree.h"
#include <vector>
#include <algorithm>
#include <limits>

#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>

#include "drawable_object.h"

class Building : public DrawableObject {

public:

    Building() {}

    Building(const Polygon& polygon, int height = 200);
    void draw(sf::RenderWindow& window, const Point& viewPoint) const override;

    float distanceToPoint(const Point& point) const override {
        return base.distanceToPoint(point);
    }

    Polygon base;
    int height;



    template<class Archive>
    void serialize(Archive& archive) {
        archive(base, height); 
    }

};

CEREAL_REGISTER_TYPE(Building);



#endif // BUILDING_H
