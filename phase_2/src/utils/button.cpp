#include <SFML/Graphics.hpp>
#include <functional>
#include "utils/button.h"


Button::Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font, const sf::Color& normalColor, const sf::Color& hoverColor, const sf::Color& clickColor)
    : normalColor(normalColor), hoverColor(hoverColor), clickColor(clickColor), isHovered(false), isClicked(false) {
    button.setSize(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(normalColor);

    buttonText.setFont(font);
    buttonText.setString(label);
    buttonText.setCharacterSize(14); // Or any other suitable size
    buttonText.setFillColor(sf::Color::White); // Set text color

    // Center text on the button
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    buttonText.setPosition(sf::Vector2f(x + width/2.0f, y + height/2.0f)); // Adjust Y position to center, -10 is a magic number for vertical alignment, may need adjustment
}

// Update the draw method to draw the text as well
void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonText);
}


void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseMoved) {
        if (button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            button.setFillColor(isClicked ? clickColor : hoverColor);
            isHovered = true;
        } else {
            button.setFillColor(normalColor);
            isHovered = false;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && isHovered) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            button.setFillColor(clickColor);
            isClicked = true;
            // Call the callback function if it's set
            if (onClick) {
                onClick();
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (isClicked) {
            button.setFillColor(isHovered ? hoverColor : normalColor);
            isClicked = false;
        }
    }
}

void Button::setOnClick(const std::function<void()>& callback) {
    onClick = callback;
}