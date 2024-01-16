#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

class Point {
public:
    float x, y;

    Point(float x, float y);
    Point() : x(0), y(0) {} // Default constructor

    // Updated equals method to take const reference
    bool equals(const Point& other) const;

    // Add default values for size and color here
    void draw(sf::RenderWindow& window, float size = 18, sf::Color color = sf::Color::Black, bool outline = false, bool fill = false) const;

    template<class Archive>
    void serialize(Archive & archive) {
        archive(x, y); // Serialize the x and y coordinates
    }
};

#endif // POINT_H
