#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <string>

#include "UI.hpp"

/**
 * Button class as an abstraction of a compound UI with Rectangular button and
 * Text. The Button is itself Drawable, a sf::RenderWindow can directly call
 * draw on this compound UI. Position of the Button will be a base position of
 * the compound UI components.
 */
namespace graphics {
class OnClickEventListener;
class Button : public UI {
 public:
  Button(Button const&) = delete;
  Button(const std::string& buttonText);
  Button(const std::string& buttonText,
         std::function<void(sf::Event)> onAction);
  ~Button();
  void setFont(const sf::Font& font);
  void setText(const std::string& text);
  void setTexture(const sf::Texture& texture);
  void setPosition(const sf::Vector2f& position);
  void setCallback(std::function<void(sf::Event)> onAction);
  virtual void setSize(const sf::Vector2f& size) override;
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

  /**
   * Setting all the position of the compound UI components to ensure everything
   * looks right.
   */
  // void setPosition(const sf::Vector2f& position);
  // virtual void setSize(const sf::Vector2f& size) override;
  // void setCallback(std::function<void(sf::Event)> onAction);

 private:
  typedef std::unique_ptr<OnClickEventListener> OCELPtr;
  static constexpr float MARGIN_X = 32.f;
  static constexpr float MARGIN_Y = 16.f;
  static constexpr int CHAR_SIZE = 32;
  sf::Text m_ButtonText;
  sf::Font m_ButtonFont;
  sf::RectangleShape m_ButtonShape;
  OCELPtr m_clickListener;
};
}  // namespace graphics
#endif
