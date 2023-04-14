#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SFML/Graphics.hpp>

#include "../GameBoard.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"

class GameScene : public Scene {
 private:
  sf::Texture m_ButtonTexture;
  sf::Font m_ButtonFont;
  Button m_QuitButton;
  Button m_SaveButton;

  GameBoard m_GameBoard;

 public:
  GameScene();
  ~GameScene();
  virtual void Update(sf::Event event) override;
  virtual void Render() override;
};

#endif
