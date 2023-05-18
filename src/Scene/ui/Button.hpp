#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <string>

#include "UI.hpp"

namespace graphics {
class OnClickEventListener;
/**
 * Button class as an abstraction of a compound UI with Rectangular button and
 * Text, it is also clickable by having OnClickEventListener. The Button is
 * itself Drawable, a sf::RenderWindow can directly call draw on this compound
 * UI. Position of the Button will be a base position of the compound UI
 * components.
 */
class Button : public UI {
 public:
  /**
   * Sets the font of the Button text
   */
  void setFont(const sf::Font* font);

  /**
   * Sets the text of the Button
   */
  void setText(const std::string& text);

  /**
   * Sets the Texture of the Button
   */
  void setTexture(const sf::Texture* texture);

  /**
   * Sets the position of the Button compound UI, this is an override to the
   * sf::Transformable as Button is a compound UI.
   */
  void setPosition(const sf::Vector2f& position);

  /**
   * Sets the callback function of OnClickEventListener for Button.
   */
  void setCallback(std::function<void(sf::Event)> onAction);

  /**
   * Sets the size of Button, this is an override to the sf::Transformable as
   * Button is a compound UI.
   */
  virtual void setSize(const sf::Vector2f& size) override;

  /**
   * We would not want a Button to be copied.
   */
  Button(Button const&) = delete;

  /**
   * Button Constructor with just the button text, the callback can be set
   * later.
   */
  Button(const std::string& buttonText);

  /**
   * Button Constructor with button text and the callback.
   */
  Button(const std::string& buttonText,
         std::function<void(sf::Event)> onAction);

  /**
   * Button Destructor.
   */
  virtual ~Button();

  /**
   * Required override by sf::Drawable, this is to render the Button.
   */
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  typedef std::unique_ptr<OnClickEventListener> OCELPtr;
  /**
   * Internal use Margin X for positioning the button text in the button.
   */
  static constexpr float MARGIN_X = 32.f;

  /**
   * Internal use Margin Y for positioning the button text in the button.
   */
  static constexpr float MARGIN_Y = 16.f;

  /**
   * Internal use of setting the right button text size.
   */
  static constexpr int CHAR_SIZE = 32;

  /**
   * The button text.
   */
  sf::Text m_ButtonText;

  /**
   * Button text's font.
   */
  sf::Font m_ButtonFont;

  /**
   * The RectangleShape for the texture of the button to be drawn on.
   */
  sf::RectangleShape m_ButtonShape;

  /**
   * OnClickEventListener that is bound to the Button.
   */
  OCELPtr m_clickListener;
};
}  // namespace graphics
#endif
