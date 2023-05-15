#ifndef WINSCENE_H
#define WINSCENE_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"

enum PlayerType { DOGE, PEPE };

class WinScene : public Scene {
 private:
  graphics::Button m_MenuButton;
  sf::RectangleShape m_WinImage;
  sf::Text m_WinMessage;

 public:
  WinScene(PlayerType);
  ~WinScene();
  virtual void Update(sf::Event event) override;
  virtual void Render() override;
};

#endif
