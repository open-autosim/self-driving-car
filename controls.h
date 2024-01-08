#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Graphics.hpp>

class Controls {
public:
    Controls();
    
    void update(const sf::RenderWindow& window);

    bool forward;
    bool left;
    bool right;
    bool reverse;
};

#endif // CONTROLS_H
