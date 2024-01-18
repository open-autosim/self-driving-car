#ifndef TARGET_H
#define TARGET_H


#include "marking.h"

class Target : public Marking {
public: 

    Target() {}

    // Using the constructor of Marking
    Target(const Point& center, const Point& directionVector, int width, int height)
        : Marking(center, directionVector, width, height) {}

    //get type
    std::string getType() const override { return "Target"; }


    void draw(sf::RenderWindow& window) const override {

        this->center.draw(window, 30, sf::Color::Red);
        this->center.draw(window, 20, sf::Color::White);
        this->center.draw(window, 10, sf::Color::Red);
       
       
    }

    template<class Archive>
    void serialize(Archive& archive) {
        archive(cereal::base_class<Marking>(this)); // Serialize base class members
    }

private:
    
};

CEREAL_REGISTER_TYPE(Target);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Marking, Target);

#endif // TARGET_H


