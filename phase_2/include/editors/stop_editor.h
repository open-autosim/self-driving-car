// StopEditor.h
#ifndef STOP_EDITOR_H
#define STOP_EDITOR_H

#include "marking_editor.h"
#include "markings/stop.h"

class StopEditor : public MarkingEditor {
public:
    StopEditor(sf::RenderWindow& window, World& world, Viewport& viewport)
        : MarkingEditor(window, world, viewport, world.getLaneGuides()) {}

    
    std::string getName() const override {
        return "Stop Editor";
    }
    
    protected:
    std::shared_ptr<Marking> createIntent(const Point& point, const Point& directionVector) override {
        return std::make_shared<Stop>(
            point, 
            directionVector, 
            world.getRoadWidth()/2, 
            world.getRoadWidth()/2);
    }



};

#endif // STOP_EDITOR_H
