// StopEditor.h
#ifndef YIELD_EDITOR_H
#define YIELD_EDITOR_H

#include "marking_editor.h"
#include "markings/yield.h"

class YieldEditor : public MarkingEditor {
public:
    YieldEditor(sf::RenderWindow& window, World& world, Viewport& viewport)
        : MarkingEditor(window, world, viewport, world.getLaneGuides()) {}

    
    std::string getName() const override {
        return "Yield Editor";
    }
    
    protected:
    std::shared_ptr<Marking> createIntent(const Point& point, const Point& directionVector) override {
        return std::make_shared<Yield>(
            point, 
            directionVector, 
            world.getRoadWidth()/2, 
            world.getRoadWidth()/2);
    }

};

#endif // YIELD_EDITOR_H
