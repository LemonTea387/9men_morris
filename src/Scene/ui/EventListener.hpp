#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <functional>

#include "SFML/Window/Event.hpp"

namespace graphics {
/**
 * EventListener is a base class for any Listeners that can be used to bind to
 * UI elements such that it is able to handle the sf::Event passed down.
 */
class EventListener {
 public:
  /**
   * Base onAction function that defines what the EventListener will perform
   * when it handles the right sf::Event.
   */
  virtual void onAction(sf::Event e) = 0;

  /**
   * Setter for the onAction function, pass in a functio that returns void but
   * handles sf::Event.
   */
  void setOnAction(std::function<void(sf::Event)> func) { fireAction = func; }

 protected:
  /**
   * The function to be fired if the right sf::Event is handled.
   */
  std::function<void(sf::Event)> fireAction;
};
}  // namespace graphics

#endif
