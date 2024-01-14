// Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    
    Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font, const sf::Color& normalColor, const sf::Color& hoverColor, const sf::Color& clickColor);

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void setOnClick(const std::function<void()>& callback);

private:
    sf::RectangleShape button;
    sf::Text buttonText;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color clickColor;
    bool isHovered;
    bool isClicked;
    std::function<void()> onClick;
};

#endif // BUTTON_H
