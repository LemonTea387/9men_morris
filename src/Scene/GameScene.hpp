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
  graphics::Button m_QuitButton;
  graphics::Button m_SaveButton;

  sf::Texture m_PlayerOneTexture;
  sf::Texture m_PlayerTwoTexture;
  sf::Texture m_TurnTexture;

  sf::Text m_PlayerOneText;
  sf::Text m_PlayerTwoText;
  sf::Text m_TurnText;

  sf::RectangleShape m_PlayerOneIcon;
  sf::RectangleShape m_PlayerTwoIcon;
  sf::RectangleShape m_TurnIcon;

  GameBoard m_GameBoard;
 public:
  GameScene();
  ~GameScene();
  virtual void Update(sf::Event event) override;
  virtual void Render() override;
};

#endif
