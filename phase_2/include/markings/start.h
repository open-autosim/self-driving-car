#ifndef START_H
#define START_H


#include "markings/marking.h"
#include "math/utils.h"

class Start : public Marking {
public: 

    Start() {

        if (!texture.loadFromFile("/Users/shlomodahan/Desktop/MCIT/open-world/phase_2/assets/car.png")) {
            std::cout << "Error loading texture" << std::endl;
        }

    }

    // Using the constructor of Marking
    Start(const Point& center, const Point& directionVector, int width, int height)
        : Marking(center, directionVector, width, height) {

            if (!texture.loadFromFile("/Users/shlomodahan/Desktop/MCIT/open-world/phase_2/assets/car.png")) {
                std::cout << "Error loading texture" << std::endl;
            }

            sprite.setTexture(texture);

            sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        }

    //get type
    std::string getType() const override { return "Start"; }
            

    void draw(sf::RenderWindow& window) const override {

        sprite.setPosition(static_cast<float>(center.x), static_cast<float>(center.y));

        float rotationAngleRadians = Utils::angle(directionVector) - M_PI/2;
        float rotationAngleDegrees = rotationAngleRadians * 180.0f / M_PI;

        sprite.setRotation(rotationAngleDegrees);  

        window.draw(sprite);
                
    }

    template<class Archive>
    void serialize(Archive& archive) {
        archive(cereal::base_class<Marking>(this)); // Serialize base class and Start-specific members
        // Note: Serialization of sf::Font is not straightforward and might need custom handling
    }

private:
    
    sf::Texture texture;
    mutable sf::Sprite sprite;
        
    
};

CEREAL_REGISTER_TYPE(Start);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Marking, Start);

#endif // START_H

