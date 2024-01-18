#include "items/tree.h"
#include "math/utils.h"

Tree::Tree(Point& center, float size, float height) : center(center), size(size), height(height) {

    base = generateLevel(center, size);
    
}

Polygon Tree::generateLevel(const Point& point, float size) const {

    std::vector<std::shared_ptr<Point>> points;
    float rad = size / 2.0f;

    for (float a = 0; a < M_PI * 2; a += M_PI / 16) {
        float kindOfRandom = pow(cos(fmod((a + this->center.x) * size, 17)), 2);
        float noisyRadius = rad * Utils::lerp(0.5f, 1.0f, kindOfRandom);
        Point noisyPoint = Utils::translate(point, a, noisyRadius);

        points.push_back(std::make_shared<Point>(noisyPoint.x, noisyPoint.y));
    }

    return Polygon(points);
}

void Tree::draw(sf::RenderWindow& window, const Point& viewPoint) const {

    Point top = Utils::get3DPoint(center, viewPoint, height);

    int levelCount = 7;
    for (int level = 0; level < levelCount; ++level) {
        float t = static_cast<float>(level) / (levelCount - 1);
        Point point = Utils::lerp2D(center, top, t);
        sf::Color color(30, static_cast<sf::Uint8>(Utils::lerp(50, 200, t)), 70);
        Polygon poly = generateLevel(point, Utils::lerp(this->size, 40.0f, t));
        poly.draw(window, sf::Color(0,0,0,0), 2, color);
        
    }
}


