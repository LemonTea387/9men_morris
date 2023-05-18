#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"

class MenuScene : public Scene {
 private:
  sf::RectangleShape m_DogeVsPepe;

  sf::RectangleShape m_TitleBackground;
  sf::Text m_TitleText;

  sf::Text m_CopyrightNotice;
  sf::Text m_CopyrightHolder;

  graphics::Button m_NewGameButton;
  graphics::Button m_CreditsButton;
  graphics::Button m_ExitButton;

 public:
  MenuScene();
  ~MenuScene();
  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif
