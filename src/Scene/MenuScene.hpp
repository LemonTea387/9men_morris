#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>

#include "SFML/Graphics/RectangleShape.hpp"
#include "Scene.hpp"

class MenuScene : public Scene {
 private:
  sf::RectangleShape m_QuitButton;
  sf::Text m_QuitText;

 public:
  MenuScene();
  ~MenuScene();
  virtual void Update(sf::Event event) override;
  virtual void Render() override;
};

#endif
