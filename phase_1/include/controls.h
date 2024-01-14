#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Graphics.hpp>
#include <string>

class Controls {
public:
    Controls(std::string controlsType);
    
    void update();

    bool forward;
    bool left;
    bool right;
    bool reverse;

private:
    std::string controlsType;
};

#endif // CONTROLS_H
