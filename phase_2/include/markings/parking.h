#ifndef PARKING_H
#define PARKING_H

#include "marking.h"

class Parking : public Marking {
public: 

    Parking() {

        if (!font.loadFromFile("/Users/shlomodahan/Desktop/MCIT/open-world/phase_2/assets/Roboto-Regular.ttf")) {
            std::cout << "Error loading font" << std::endl;
        }

    }

    // Using the constructor of Marking
    Parking(const Point& center, const Point& directionVector, int width, int height)
        : Marking(center, directionVector, width, height) {
            
            // Load the font

            if (!font.loadFromFile("/Users/shlomodahan/Desktop/MCIT/open-world/phase_2/assets/Roboto-Regular.ttf")) {
            std::cout << "Error loading font" << std::endl;
            }
            borders = {poly.segments[0], poly.segments[2]};
        }

    //get type
    std::string getType() const override { return "Parking"; }


    void draw(sf::RenderWindow& window) const override {

        for (auto border : borders) {
            border.draw(window, 5, sf::Color::White);
        }

        // Draw the text
        sf::Text text;
        text.setString("P");
        text.setFont(font);
        text.setCharacterSize(static_cast<unsigned int>(height * 0.9));
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

        float rotationAngleDegrees = Utils::angle(directionVector) * 180.0f / M_PI;
        text.setRotation(rotationAngleDegrees);
        text.setPosition(sf::Vector2f(center.x, center.y + 3));

        window.draw(text);
    }


    template<class Archive>
    void serialize(Archive& archive) {
        archive(cereal::base_class<Marking>(this), borders); // Serialize base class and Parking-specific members
        // Note: Serialization of sf::Font is not straightforward and might need custom handling
    }

private:
    
    std::vector<Segment> borders;
    sf::Font font;
};

CEREAL_REGISTER_TYPE(Parking);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Marking, Parking);

#endif // PARKING_H


