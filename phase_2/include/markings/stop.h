#ifndef STOP_H
#define STOP_H

#include "marking.h"

class Stop : public Marking {
public: 

    Stop() {
        
        if (!font.loadFromFile("/Users/shlomodahan/Desktop/MCIT/open-world/phase_2/assets/Roboto-Regular.ttf")) {
            std::cout << "Error loading font" << std::endl;
        }
    }


    // Using the constructor of Marking
    Stop(const Point& center, const Point& directionVector, int width, int height)
        : Marking(center, directionVector, width, height) {
            
            // Load the font

            if (!font.loadFromFile("/Users/shlomodahan/Desktop/MCIT/open-world/phase_2/assets/Roboto-Regular.ttf")) {
            std::cout << "Error loading font" << std::endl;
            }
            border = poly.segments[2];
        }

    //get type
    std::string getType() const override { return "Stop"; }

    void draw(sf::RenderWindow& window) const override {

        // std::cout << "Drawing stop" << std::endl;

        // Draw the border
        border.draw(window, 5, sf::Color::White);

        // Draw the text
        sf::Text text;
        text.setString("STOP");
        text.setFont(font);
        text.setCharacterSize(static_cast<unsigned int>(height * 0.3));
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        // text.setScale(1, 2);

        // Set the origin, rotation, and position of the text
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
        float rotationAngleRadians = Utils::angle(directionVector) - M_PI/2;
        float rotationAngleDegrees = rotationAngleRadians * 180.0f / M_PI;
        text.setRotation(rotationAngleDegrees);
        text.setPosition(sf::Vector2f(center.x, center.y));

        // Draw the text
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

CEREAL_REGISTER_TYPE(Stop);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Marking, Stop);


#endif // STOP_H