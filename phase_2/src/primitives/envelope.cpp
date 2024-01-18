#include "primitives/envelope.h"

Envelope::Envelope(Segment& segment, int width, int roundness) : skeleton(segment), width(width), roundness(roundness) {
    polygon = generatePolygon(width, roundness);
}

Polygon Envelope::generatePolygon(int width, int roundness) {

    std::vector<std::shared_ptr<Point>> points;

    //get the two points from skeleton
    std::shared_ptr<Point> p1 = skeleton.p1;
    std::shared_ptr<Point> p2 = skeleton.p2;

    float radius = width/2;
    float alpha = Utils::angle(Utils::subtract(*p1, *p2));
    float alpha_cw = alpha + M_PI/2;
    float alpha_ccw = alpha - M_PI/2;

    float step = M_PI/std::max(1, roundness);
    float eps = step/2;

    for (double i = alpha_ccw; i <= alpha_cw + eps; i += step) {
        Point translatedPoint = Utils::translate(*p1, i, radius);
        points.emplace_back(std::make_shared<Point>(translatedPoint));
    }

    for (double i = alpha_ccw; i <= alpha_cw + eps; i += step) {
        Point translatedPoint = Utils::translate(*p2, M_PI + i, radius);
        points.emplace_back(std::make_shared<Point>(translatedPoint));
    }

    return Polygon(points);
}

void Envelope::draw(sf::RenderWindow& window, sf::Color stroke, int linewidth, sf::Color fill) const {
    polygon.draw(window, stroke, linewidth, fill);
}