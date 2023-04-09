#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.hpp"

class MenuScene : public Scene {
 public:
  MenuScene();
  virtual void Update() override;
  virtual void Render() override;
};

#endif
