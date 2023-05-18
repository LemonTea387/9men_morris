#ifndef UI_H
#define UI_H

#include <functional>
#include <vector>

#include "EventListener.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System/Vector2.hpp"

/**
 * Typically everything related to graphics that we created.
 */
namespace graphics {
/**
 * Base UI class that can Listen to events with EventListener.
 * If any specialised UI we create needs to be able to handle events, they can
 * derive from this UI class.
 */
class UI : public sf::Drawable, public sf::Transformable {
 public:
  /**
   * For custom size calculations of compound UI elements
   */
  virtual void setSize(const sf::Vector2f& size) { m_size = size; }

  /**
   * For custom size calculations of compound UI elements.
   */
  const sf::Vector2f& getSize() { return m_size; }

  /**
   * Register an EventListener onto the UI.
   */
  void addEventListener(EventListener* el) { m_listeners.emplace_back(el); }

  /**
   * Notify the bounded EventListeners for any sf::Event to be handled by the
   * EventListeners.
   */
  void notifyListeners(sf::Event e) {
    for (auto& listener : m_listeners) {
      listener->onAction(e);
    }
  }

 private:
  /**
   * Custom Size attribute for customizable compound UI elements.
   */
  sf::Vector2f m_size{};

  /**
   * All the EventListeners that are bounded to this UI element.
   */
  std::vector<EventListener*> m_listeners{};
};
}  // namespace graphics

#endif
