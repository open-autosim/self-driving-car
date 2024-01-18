#ifndef WORLD_H
#define WORLD_H

#include "math/graph.h"
#include "primitives/envelope.h"
#include "primitives/polygon.h"
#include "items/tree.h"
#include "items/building.h"
#include <vector>
#include <algorithm> 
#include <limits>
#include <SFML/Graphics.hpp>
#include "markings/marking.h"
#include "markings/light.h"
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>


class World {

public:
    
    World(Graph& graph, 
        int roadWidth = 100, 
        int roadRoundness = 10,
        int buildingWidth = 150, 
        int buildingMinLength = 150,
        int spacing = 50,
        int treeSize = 160
    );

    void draw(sf::RenderWindow& window, const Point& viewPoint) const;

    void generate();
    std::vector<Building> generateBuildings();
    std::vector<Tree> generateTrees();
    std::vector<Segment> generateLaneGuides();

    std::vector<std::shared_ptr<Point>> getIntersections() const;

    void updateLights() const;

    // get graph
    Graph& getGraph() { return graph; }
    int getRoadWidth() const { return roadWidth; }

    //method to add markings
    void addMarking(std::shared_ptr<Marking> marking) {
        markings.push_back(marking);
    }

    //method to get markings
    std::vector<std::shared_ptr<Marking>>& getMarkings() {
        return markings;
    }

    // In world.h
    std::vector<Segment>& getLaneGuides() { return laneGuides; }

    std::vector<Segment>& getRoadBorders() { return roadBorders; }
    

    //method to clear markings
    void clearWorld() {
        // graph.dispose();
        markings.clear();
        buildings.clear();
        trees.clear();
    }

    // template<class Archive>
    // void serialize(Archive & archive) {
    //     archive(graph, roadWidth, roadRoundness, buildingWidth, buildingMinLength, spacing, treeSize, buildings, trees, markings, laneGuides, roadBorders, envelopes);
    // }

    void save() const;
    bool load();

    template<class Archive>
    void serialize(Archive & archive) {
        archive(graph, roadWidth, roadRoundness, buildingWidth, buildingMinLength, spacing, treeSize, buildings, trees, envelopes, roadBorders, laneGuides, markings, zoom, offset);
    }
    
    float zoom;
    Point offset;

private:
    /* data */
    Graph& graph;
    int roadWidth;
    int roadRoundness;
    int buildingWidth;
    int buildingMinLength;
    int spacing;
    int treeSize;   
    mutable int frameCount = 0;


    std::vector<Envelope> envelopes;
    std::vector<Segment> roadBorders;
    std::vector<Building> buildings;
    std::vector<Tree> trees;
    std::vector<Segment> laneGuides;

    std::vector<std::shared_ptr<Marking>> markings;



};

#endif // WORLD_H
