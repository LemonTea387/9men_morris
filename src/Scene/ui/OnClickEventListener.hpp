#ifndef ONCLICK_EVENTLISTENER_H
#define ONCLICK_EVENTLISTENER_H

#include <iostream>

#include "EventListener.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Window/Mouse.hpp"
#include "UI.hpp"

namespace graphics {
/**
 * A special EventListener that specifically handles
 * sf::Event::MouseButtonReleased, or in other words, Mouse Click releases on
 * the UI element
 */
class OnClickEventListener : public EventListener {
 public:
  /**
   * OnClickEventListener Constructor, has the UI pointer to know what are the
   * bounds to check for the sf::Event::MouseButtonReleased.
   */
  OnClickEventListener(UI* ui, std::function<void(sf::Event)> func) {
    m_ui = ui;
    setOnAction(func);
  };

  /**
   * OnClickEventListener Destructor.
   */
  ~OnClickEventListener() {}

  /**
   * If the Click is detected in the bounds of the UI element the
   * OnClickEventListener is bound to, it will activate the fireAction
   */
  virtual void onAction(sf::Event e) {
    if (e.type == sf::Event::MouseButtonReleased &&
        e.mouseButton.button == sf::Mouse::Left) {
      if (sf::Rect<float>(m_ui->getPosition(), m_ui->getSize())
              .contains(e.mouseButton.x, e.mouseButton.y)) {
        fireAction(e);
      }
    }
  };

 private:
  /**
   * The UI element this OnClickEventListener is bound to. Used to check the
   * bounds against the position of the sf::Event::MouseButtonReleased.
   */
  UI* m_ui;
};
}  // namespace graphics
#endif
