#include "Button.hpp"

#include "OnClickEventListener.hpp"
#include "SFML/System/Vector2.hpp"

namespace graphics {
Button::Button(const std::string& buttonText) {
  m_ButtonText.setString(buttonText);
  m_ButtonText.setCharacterSize(CHAR_SIZE);
  m_ButtonText.setFillColor(sf::Color(0xd0, 0xbc, 0xff));

  // TODO : Remove this expensive workaround to fix SFML width = 0 bug with AssetManager
  if (!m_ButtonFont.loadFromFile(
          "assets/fonts/Comfortaa/static/Comfortaa-SemiBold.ttf")) {
    std::cerr << "Could not load ButtonFont" << std::endl;
  }
  m_ButtonText.setFont(m_ButtonFont);

  setSize(
      sf::Vector2f(m_ButtonText.getLocalBounds().width + Button::MARGIN_X * 2,
                   CHAR_SIZE + Button::MARGIN_Y * 2));
}

Button::Button(const std::string& buttonText,
               std::function<void(sf::Event)> onAction)
    : Button(buttonText) {
  m_clickListener = std::make_unique<OnClickEventListener>(this, onAction);
  addEventListener(m_clickListener.get());
}

Button::~Button() {}

void Button::setFont(const sf::Font& font) { m_ButtonText.setFont(font); };

void Button::setText(const std::string& text) { m_ButtonText.setString(text); };

void Button::setTexture(const sf::Texture& texture) {
  m_ButtonShape.setTexture(&texture, true);
  UI::setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
};

void Button::setPosition(const sf::Vector2f& position) {
  // Might need to set position of actual Button from sf::Transformable to
  // ensure getPosition returns the right thing.
  sf::Transformable::setPosition(position);
  m_ButtonShape.setPosition(position);
  m_ButtonText.setPosition(sf::Vector2f(position.x + Button::MARGIN_X,
                                        position.y + Button::MARGIN_Y));
}

void Button::setCallback(std::function<void(sf::Event)> onAction) {
  m_clickListener = std::make_unique<OnClickEventListener>(this, onAction);
  addEventListener(m_clickListener.get());
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
