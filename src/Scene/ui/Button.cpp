#include "Button.hpp"

#include "OnClickEventListener.hpp"
#include "SFML/System/Vector2.hpp"

namespace graphics {
Button::Button(const std::string& buttonText,
               std::function<void(sf::Event)> onAction)
    : m_clickListener(this, onAction) {
  m_ButtonText.setString(buttonText);
  m_ButtonText.setCharacterSize(CHAR_SIZE);
  m_ButtonText.setFillColor(sf::Color(0xd0, 0xbc, 0xff));

  // TODO : Calculate dynamically
  m_ButtonShape.setSize(
      sf::Vector2f((buttonText.length() - 1) * CHAR_SIZE + Button::MARGIN_X * 2,
                   CHAR_SIZE + Button::MARGIN_Y * 2));
  setSize(m_ButtonShape.getSize());

  addEventListener(&m_clickListener);
}

void Button::setTexture(const sf::Texture& texture) {
  m_ButtonShape.setTexture(&texture, true);
}

void Button::setFont(const sf::Font& font) { m_ButtonText.setFont(font); }

void Button::setText(const std::string& text) { m_ButtonText.setString(text); }

Button::~Button() {}

void Button::setPosition(const sf::Vector2f& position) {
  // Might need to set position of actual Button from sf::Transformable to
  // ensure getPosition returns the right thing.
  sf::Transformable::setPosition(position);
  m_ButtonShape.setPosition(position);
  m_ButtonText.setPosition(sf::Vector2f(position.x + Button::MARGIN_X,
                                        position.y + Button::MARGIN_Y));
}

void Button::setSize(const sf::Vector2f& size) {
  UI::setSize(size);
  m_ButtonShape.setSize(size);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(m_ButtonShape);
  target.draw(m_ButtonText);
}
}  // namespace graphics
