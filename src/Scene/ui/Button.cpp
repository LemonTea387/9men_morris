#include "Button.hpp"

#include <iostream>

Button::Button() {
}

Button::Button(const sf::Texture& texture,const sf::Font& font, const std::string& buttonText) {
    m_ButtonShape.setTexture(&texture);
    m_ButtonText.setFont(font);
    

    m_ButtonText.setString(buttonText);
    m_ButtonText.setCharacterSize(CHAR_SIZE);
    m_ButtonText.setFillColor(sf::Color(0xd0, 0xbc, 0xff));

    // TODO : Calculate dynamically
    m_ButtonShape.setSize(sf::Vector2f((buttonText.length() - 1) * CHAR_SIZE + Button::MARGIN_X * 2,
                        CHAR_SIZE +  Button::MARGIN_Y*2));
}

Button::~Button() {

}

void Button::setPosition(const sf::Vector2f& position) {
    // Might need to set position of actual Button from sf::Transformable to ensure 
    // getPosition returns the right thing.
    m_ButtonShape.setPosition(position);
    m_ButtonText.setPosition(sf::Vector2f(position.x + Button::MARGIN_X, position.y + Button::MARGIN_Y));
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_ButtonShape);
    target.draw(m_ButtonText);
}
