#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>

#include "SFML/Graphics/RectangleShape.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"

class MenuScene : public Scene {
 private:
  // TO-DO: Use a Button class (with rounded corners, hover support, etc.)
  sf::RectangleShape m_DogeVsPepe;
  sf::Texture m_DogeVsPepeTexture;

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
