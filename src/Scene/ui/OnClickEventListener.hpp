#ifndef ONCLICK_EVENTLISTENER_H
#define ONCLICK_EVENTLISTENER_H

#include <iostream>

#include "EventListener.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window/Mouse.hpp"
#include "UI.hpp"

namespace graphics {
class OnClickEventListener : public EventListener {
 public:
  OnClickEventListener(UI* ui, std::function<void(sf::Event)> func) {
    m_ui = ui;
    setOnAction(func);
  };

  ~OnClickEventListener() {}
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
  UI* m_ui;
};
}  // namespace graphics
#endif
