#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <functional>
#include "SFML/Window/Event.hpp"

namespace graphics {
class EventListener{
public:
  virtual void onAction(sf::Event e) = 0;
  void setOnAction(std::function<void(sf::Event)> func)
  {
    fireAction = func;
  }

protected:
  std::function<void(sf::Event)> fireAction;
};
}  // namespace graphics

#endif
