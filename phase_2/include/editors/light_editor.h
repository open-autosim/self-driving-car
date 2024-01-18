// StopEditor.h
#ifndef LIGHT_EDITOR_H
#define LIGHT_EDITOR_H

#include "marking_editor.h"
#include "markings/light.h"

class LightEditor : public MarkingEditor {
public:
    LightEditor(sf::RenderWindow& window, World& world, Viewport& viewport)
        : MarkingEditor(window, world, viewport, world.getLaneGuides()) {}

    
    std::string getName() const override {
        return "Light Editor";
    }
    
    protected:
    std::shared_ptr<Marking> createIntent(const Point& point, const Point& directionVector) override {
        return std::make_shared<Light>(
            point, 
            directionVector, 
            world.getRoadWidth()/2, 
            world.getRoadWidth()/2);
    }



};

#endif // 
