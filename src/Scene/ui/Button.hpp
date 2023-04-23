#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

#include "OnClickEventListener.hpp"
#include "UI.hpp"

/**
 * Button class as an abstraction of a compound UI with Rectangular button and
 * Text. The Button is itself Drawable, a sf::RenderWindow can directly call
 * draw on this compound UI. Position of the Button will be a base position of
 * the compound UI components.
 */
namespace graphics {
class Button : public UI {
 public:
  Button(Button const&) = delete;
  Button(const std::string& buttonText,
         std::function<void(sf::Event)> onAction);
  ~Button();
  void setTexture(const sf::Texture& texture);
  void setFont(const sf::Font& font);
  void setText(const std::string& text);

  /**
   * Setting all the position of the compound UI components to ensure everything
   * looks right.
   */
  void setPosition(const sf::Vector2f& position);
  virtual void setSize(const sf::Vector2f& size) override;

 private:
  static constexpr float MARGIN_X = 32.f;
  static constexpr float MARGIN_Y = 16.f;
  static constexpr int CHAR_SIZE = 32;
  sf::RectangleShape m_ButtonShape;
  sf::Text m_ButtonText;
  sf::Font m_ButtonFont;
  OnClickEventListener m_clickListener;
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};
}  // namespace graphics
#endif