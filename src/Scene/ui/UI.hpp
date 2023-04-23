#ifndef UI_H
#define UI_H

#include <functional>
#include <vector>

#include "EventListener.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System/Vector2.hpp"

namespace graphics {
class UI : public sf::Drawable, public sf::Transformable {
 public:
  virtual void setSize(const sf::Vector2f& size) { m_size = size; }
  const sf::Vector2f& getSize() { return m_size; }
  void addEventListener(EventListener * el) {
    m_listeners.emplace_back(el);
  }
  void notifyListeners(sf::Event e) {
    for (auto& listener : m_listeners) {
      listener->onAction(e);
    }
  }

 private:
  sf::Vector2f m_size{};
  std::vector<EventListener*> m_listeners{};
};
}  // namespace graphics

#endif
