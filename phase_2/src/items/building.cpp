#include "items/building.h"

Building::Building(const Polygon& polygon, int height) : base(polygon), height(height) {

    
}


void Building::draw(sf::RenderWindow& window, const Point& viewPoint) const {

    // array of shared pointers to points
    std::vector<std::shared_ptr<Point>> topPoints;
    for (auto& point : base.points) {
        topPoints.push_back(std::make_shared<Point>(Utils::get3DPoint(*point, viewPoint, height*0.6)));
    }
    Polygon ceiling(topPoints);

    std::vector<Polygon> sides;
    for (int i = 0; i < base.points.size(); i++) {
        int nextIndex = (i + 1) % base.points.size();
        Polygon poly = Polygon({base.points[i], base.points[nextIndex], topPoints[nextIndex], topPoints[i]});
        sides.push_back(poly);
    }
    //sort the sides by distance to viewPoint
    std::sort(sides.begin(), sides.end(), [&viewPoint](const Polygon& a, const Polygon& b) {
        return a.distanceToPoint(viewPoint) > b.distanceToPoint(viewPoint);
    });

    //vector of base midpoints
    std::vector<Point> baseMidpoints;
    baseMidpoints.push_back(Utils::average(*base.points[0], *base.points[1]));
    baseMidpoints.push_back(Utils::average(*base.points[2], *base.points[3]));

    std::vector<std::shared_ptr<Point>> topMidpoints;
    for (auto& p : baseMidpoints) {
        topMidpoints.push_back(std::make_shared<Point>(Utils::get3DPoint(p, viewPoint, height)));
    }

    // Create roof polygons
    std::vector<Polygon> roofPolys;
    roofPolys.push_back(Polygon({ceiling.points[0], ceiling.points[3], topMidpoints[1], topMidpoints[0]}));
    roofPolys.push_back(Polygon({ceiling.points[2], ceiling.points[1], topMidpoints[0], topMidpoints[1]}));

    // sort roof polys just like sides
    std::sort(roofPolys.begin(), roofPolys.end(), [&viewPoint](const Polygon& a, const Polygon& b) {
        return a.distanceToPoint(viewPoint) > b.distanceToPoint(viewPoint);
    });

    base.draw(window, sf::Color(0,0,0,50), 20, sf::Color::White);
    
    for (auto& side : sides) {
        side.draw(window, sf::Color(170,170,170), 2, sf::Color::White);
    }

    ceiling.draw(window, sf::Color::White, 6, sf::Color::White);

    for (auto& roof : roofPolys) {
        roof.draw(window, sf::Color(204,68,68), 8, sf::Color(221,68,68));
    }

    
}
