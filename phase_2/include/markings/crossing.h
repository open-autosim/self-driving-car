#ifndef CROSSING_H
#define CROSSING_H

#include "markings/marking.h"
#include <cereal/types/polymorphic.hpp>

class Crossing : public Marking {
public: 

    Crossing() {}

    // Using the constructor of Marking
    Crossing(const Point& center, const Point& directionVector, int width, int height)
        : Marking(center, directionVector, width, height) {
            
            borders = { poly.segments[0], poly.segments[2] } ;
        }

    //get type
    std::string getType() const override { return "Crossing"; }

    void draw(sf::RenderWindow& window) const override {
        
        Point perp = Utils::perpendicular(directionVector);
        Segment line = Segment(
            std::make_shared<Point>(Utils::add(center, Utils::scale(perp, width/2))),
            std::make_shared<Point>(Utils::add(center, Utils::scale(perp, -width/2)))
        );
        line.draw(window, height, sf::Color::White, true);

        
        line.draw(window, height, sf::Color::White, true, 11, 11);
        
    }


    template<class Archive>
    void serialize(Archive& archive) {
        archive(cereal::base_class<Marking>(this), borders); // Serialize base class and Crossing-specific members
    }

private:
    
    std::vector<Segment> borders;
    
};

CEREAL_REGISTER_TYPE(Crossing);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Marking, Crossing);

#endif // CROSSING_H

