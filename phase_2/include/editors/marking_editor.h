#ifndef MARKING_EDITOR_H
#define MARKING_EDITOR_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "world.h"
#include "viewport.h"
#include "primitives/point.h"
#include "primitives/segment.h"
#include "markings/marking.h"



class MarkingEditor {
public:

    MarkingEditor(sf::RenderWindow& window, World& world, Viewport& viewport, std::vector<Segment>& targetSegments)
        : window(window), world(world), viewport(viewport), mouseEnabled(false), targetSegments(targetSegments) {}

    virtual ~MarkingEditor() {}

    virtual std::string getName() const = 0;

    void handleEvent(const sf::Event& event) {
        if (!mouseEnabled) {
            return;
        }
         if (event.type == sf::Event::MouseMoved) {
            handleMouseMove(event);
        } else if (event.type == sf::Event::MouseButtonPressed) {
            handleMouseDown(event);
        }
    }

    void enable() {
        mouseEnabled = true;
    }

    void disable() {
        mouseEnabled = false;
    }

    bool isMouseEnabled() const {
        return mouseEnabled;
    }

    void display() {
        if (intent) {
            intent->draw(window);
        }


    }


protected:
    virtual std::shared_ptr<Marking> createIntent(const Point& point, const Point& directionVector) = 0;
    virtual void handleMouseDown(const sf::Event& event) {
        // Implement mouse down behavior or leave empty to be defined in subclasses
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (intent) {
                world.addMarking(intent);
                intent = nullptr;
            }
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            auto& markings = world.getMarkings(); // Reference to the markings vector
            for (auto it = markings.begin(); it != markings.end(); /* no increment here */) {
                if ((*it)->getPolygon().containsPoint(*mouse)) {
                    it = markings.erase(it); // Erase returns the next valid iterator
                } else {
                    ++it; // Only increment if you didn't erase
                }
            }
        }
    }

    void handleMouseMove(const sf::Event& event) {

        Point mousePos = viewport.getMouse(event, true);
        mouse = std::make_shared<Point>(mousePos.x, mousePos.y);
        std::shared_ptr<Segment> segIntent = Segment::getNearestSegment(mousePos, targetSegments, 10 * viewport.getZoom());

        if (segIntent) {
            Utils::IntersectionResult proj = segIntent->projectPoint(mousePos);
            if (proj.offset >= 0 && proj.offset <= 1) {
                intent = createIntent(proj.point, segIntent->directionVector());
            } else {
                intent = nullptr;
            }
        } else {
            segIntent = nullptr;
            intent = nullptr;
        }
    }

    
    sf::RenderWindow& window;
    World& world;
    Viewport& viewport;
    std::shared_ptr<Point> mouse;
    std::shared_ptr<Segment> segIntent;
    std::vector<Segment>& targetSegments;

    std::shared_ptr<Marking> intent;
    bool mouseEnabled;
};

#endif // MARKING_EDITOR_H
