#ifndef LIGHT_H
#define LIGHT_H

#include "markings/marking.h"
#include "math/utils.h"

class Light : public Marking {
public: 

    Light() {}

    enum class State {
        Off,
        Green,
        Yellow,
        Red
    };

    // Using the constructor of Marking
    Light(const Point& center, const Point& directionVector, int width, int height)
        : Marking(center, directionVector, width, 18) {

            state = State::Off;
            border = poly.segments[0];
        }

    //get type
    std::string getType() const override { return "Light"; }

    //set state
    void setState(State state) { this->state = state; }
            

    void draw(sf::RenderWindow& window) const override {

        Point perp = Utils::perpendicular(directionVector); 
        Segment line = Segment(
            std::make_shared<Point>(Utils::add(center, Utils::scale(perp, width/2))),
            std::make_shared<Point>(Utils::add(center, Utils::scale(perp, -width/2)))
        );

        Point green = Utils::lerp2D(*line.p1, *line.p2, 0.2);
        Point yellow = Utils::lerp2D(*line.p1, *line.p2, 0.5);
        Point red = Utils::lerp2D(*line.p1, *line.p2, 0.8);

        Segment seg(std::make_shared<Point>(red), std::make_shared<Point>(green));
        seg.draw(window, height);

        green.draw(window, height*0.6, sf::Color(0,102,0));
        yellow.draw(window, height*0.6, sf::Color(102,102,0));
        red.draw(window, height*0.6, sf::Color(102,0,0));

        switch (state) {
            case State::Green:
                green.draw(window, height*0.6, sf::Color(0,255,0));
                break;
            case State::Yellow:
                yellow.draw(window, height*0.6, sf::Color(255,255,0));
                break;
            case State::Red:
                red.draw(window, height*0.6, sf::Color(255,0,0));
                break;
            default:
                break;
        }
                
    }


    template<class Archive>
    void serialize(Archive& archive) {
        archive(cereal::base_class<Marking>(this), state, border); // Serialize base class and Light-specific members
    }


private:
    
    State state;
    Segment border;
        
    
};

CEREAL_REGISTER_TYPE(Light);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Marking, Light);

#endif // LIGHT_H

