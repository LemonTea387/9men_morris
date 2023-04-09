#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
class Scene {
 public:
  virtual void Update(sf::Event event) = 0;
  virtual void Render() = 0;
};

#endif
