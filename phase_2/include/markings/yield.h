#ifndef YIELD_H
#define YIELD_H

#include "marking.h"

class Yield : public Marking {
public: 

    
    Yield() {
        if (!font.loadFromFile("/Users/shlomodahan/Desktop/MCIT/open-world/phase_2/assets/Roboto-Regular.ttf")) {
        std::cout << "Error loading font" << std::endl;
        }
    }

    // Using the constructor of Marking
    Yield(const Point& center, const Point& directionVector, int width, int height)
        : Marking(center, directionVector, width, height) {
            
            // Load the font

            if (!font.loadFromFile("/Users/shlomodahan/Desktop/MCIT/open-world/phase_2/assets/Roboto-Regular.ttf")) {
            std::cout << "Error loading font" << std::endl;
            }
            border = poly.segments[2];
        }

    //get type
    std::string getType() const override { return "Yield"; }

    void draw(sf::RenderWindow& window) const override {

        border.draw(window, 5, sf::Color::Yellow);

        // Draw the text
        sf::Text text;
        text.setString("YIELD");
        text.setFont(font);
        text.setCharacterSize(static_cast<unsigned int>(height * 0.3));
        text.setFillColor(sf::Color::Yellow);
        text.setStyle(sf::Text::Bold);

        //scale the text
        text.setScale(1, 2);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

        float rotationAngleDegrees = (Utils::angle(directionVector) - M_PI/2) * 180.0f / M_PI;
        text.setRotation(rotationAngleDegrees);
        text.setPosition(sf::Vector2f(center.x, center.y + 3));

        window.draw(text);
    }

    template<class Archive>
    void serialize(Archive& archive) {
        archive(cereal::base_class<Marking>(this), border); 
        // Note: Serialization of sf::Font is not straightforward and might need custom handling
    }

private:
    
    Segment border;
    sf::Font font;
};

CEREAL_REGISTER_TYPE(Yield);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Marking, Yield);

#endif // YIELD_H


