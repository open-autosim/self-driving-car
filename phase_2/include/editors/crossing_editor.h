// StopEditor.h
#ifndef CROSSING_EDITOR_H
#define CROSSING_EDITOR_H   


#include "marking_editor.h"
#include "markings/crossing.h"

class CrossingEditor : public MarkingEditor {
public:
    CrossingEditor(sf::RenderWindow& window, World& world, Viewport& viewport)
        : MarkingEditor(window, world, viewport, world.getGraph().getSegments()) {}

    
    std::string getName() const override {
        return "Crossing Editor";
    }

    protected:
    std::shared_ptr<Marking> createIntent(const Point& point, const Point& directionVector) override {
        return std::make_shared<Crossing>(point, 
        directionVector, 
        world.getRoadWidth(), 
        world.getRoadWidth()/2);
    }

};

#endif // CROSSING_EDITOR_H