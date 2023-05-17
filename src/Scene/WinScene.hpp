#ifndef WINSCENE_H
#define WINSCENE_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"

enum WinnerType { DOGE, PEPE, TIE };

class WinScene : public Scene {
 private:
  graphics::Button m_MenuButton;
  sf::RectangleShape m_WinImage;
  sf::Text m_WinMessage;

 public:
  WinScene(WinnerType wt);
  ~WinScene();
  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif
