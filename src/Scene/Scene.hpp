#ifndef SCENE_H
#define SCENE_H
#include "../GameObject.hpp"
class Scene : public GameObject {
 public:
  virtual void Update(sf::Event event) = 0;
  virtual void Render() = 0;
};

#endif
