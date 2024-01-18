// StopEditor.h
#ifndef TARGET_EDITOR_H
#define TARGET_EDITOR_H

#include "marking_editor.h"
#include "markings/target.h"

class TargetEditor : public MarkingEditor {
public:
    TargetEditor(sf::RenderWindow& window, World& world, Viewport& viewport)
        : MarkingEditor(window, world, viewport, world.getLaneGuides()) {}

    
    std::string getName() const override {
        return "Target Editor";
    }
    
    protected:
    std::shared_ptr<Marking> createIntent(const Point& point, const Point& directionVector) override {
        return std::make_shared<Target>(
            point, 
            directionVector, 
            world.getRoadWidth()/2, 
            world.getRoadWidth()/2);
    }



};

#endif // TARGET_EDITOR_H
