#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <vector>
#include <memory> // Add the necessary include statement
#include <SFML/Graphics.hpp>
#include "primitives/point.h"
#include "primitives/segment.h"
#include "primitives/polygon.h"
#include "math/utils.h"
#include <cmath>   
#include <algorithm>

class Envelope {

public:    

    Envelope() {}
    Envelope(Segment& segment, int width, int roundness = 1);
    Polygon generatePolygon(int width, int roundness);
    void draw(sf::RenderWindow& window, sf::Color stroke = sf::Color::Blue, int linewidth = 2, sf::Color fill = sf::Color(0, 0, 255, 50)) const;
    
    Polygon polygon;

    template<class Archive>
    void serialize(Archive& archive) {
        archive(polygon, skeleton, width, roundness); 
    }

private:
    Segment skeleton;  
    int width;
    int roundness;
};

#endif 
