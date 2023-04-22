#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SFML/Graphics.hpp>

class GameObject {
 public:
  virtual void Update(sf::Event event) = 0;
  virtual void Render() = 0;
};
#endif
