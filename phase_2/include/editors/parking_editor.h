// StopEditor.h
#ifndef PARKING_EDITOR_H
#define PARKING_EDITOR_H

#include "marking_editor.h"
#include "markings/parking.h"

class ParkingEditor : public MarkingEditor {
public:
    ParkingEditor(sf::RenderWindow& window, World& world, Viewport& viewport)
        : MarkingEditor(window, world, viewport, world.getLaneGuides()) {}

    
    std::string getName() const override {
        return "Parking Editor";
    }
    
    protected:
    std::shared_ptr<Marking> createIntent(const Point& point, const Point& directionVector) override {
        return std::make_shared<Parking>(
            point, 
            directionVector, 
            world.getRoadWidth()/2, 
            world.getRoadWidth()/2);
    }



};

#endif // PARKING_EDITOR_H
