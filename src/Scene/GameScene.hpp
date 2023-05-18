#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "Scene.hpp"
#include "ui/Button.hpp"
#include "../Token.hpp"
class GameBoard;

class GameScene : public Scene {
 private:
  Token::Occupation m_PrevTurn;
  graphics::Button m_QuitButton;
  graphics::Button m_SaveButton;

  sf::Text m_PlayerOneText;
  sf::Text m_PlayerTwoText;
  sf::Text m_TurnText;

  sf::RectangleShape m_PlayerOneIcon;
  sf::RectangleShape m_PlayerTwoIcon;
  sf::RectangleShape m_TurnIcon;

  sf::Texture* m_PlayerOneTexture;
  sf::Texture* m_PlayerTwoTexture;

  std::unique_ptr<GameBoard> m_GameBoard;

 public:
  GameScene();
  ~GameScene();
  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif
