#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>

#include "SFML/Graphics/RectangleShape.hpp"
#include "Scene.hpp"

class MenuScene : public Scene {
 private:
  sf::RectangleShape m_QuitButton;

 public:
  MenuScene();
  ~MenuScene();
  virtual void Update() override;
  virtual void Render() override;
};

#endif
