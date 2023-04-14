#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SFML/Graphics.hpp>

#include "SFML/Graphics/RectangleShape.hpp"
#include "Scene.hpp"

class GameScene : public Scene {
 private:
  sf::RectangleShape m_Board;
  sf::Texture m_BoardTexture;

 public:
  GameScene();
  ~GameScene();
  virtual void Update(sf::Event event) override;
  virtual void Render() override;
};

#endif
