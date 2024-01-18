// StopEditor.h
#ifndef START_EDITOR_H
#define START_EDITOR_H

#include "marking_editor.h"
#include "markings/start.h"

class StartEditor : public MarkingEditor {
public:
    StartEditor(sf::RenderWindow& window, World& world, Viewport& viewport)
        : MarkingEditor(window, world, viewport, world.getLaneGuides()) {}

    
    std::string getName() const override {
        return "Start Editor";
    }
    
    protected:
    std::shared_ptr<Marking> createIntent(const Point& point, const Point& directionVector) override {
        return std::make_shared<Start>(
            point, 
            directionVector, 
            world.getRoadWidth()/2, 
            world.getRoadWidth()/2);
    }



};

#endif // START_EDITOR_H
