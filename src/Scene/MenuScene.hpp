#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>

#include "SFML/Graphics/RectangleShape.hpp"
#include "Scene.hpp"

class MenuScene : public Scene {
 private:
  // TO-DO: Use a Button class (with rounded corners, hover support, etc.)
  sf::RectangleShape m_NewGameButton;
  sf::RectangleShape m_ConGameButton;
  sf::RectangleShape m_CreditsButton;
  sf::RectangleShape m_ExitButton;
  sf::RectangleShape m_DogeVsPepe;
  sf::Text m_NewGameText;
  sf::Text m_ConGameText;
  sf::Text m_CreditsText;
  sf::Text m_ExitText;
  sf::Texture m_NewGameTexture;
  sf::Texture m_ConGameTexture;
  sf::Texture m_CreditsTexture;
  sf::Texture m_ExitTexture;
  sf::Texture m_DogeVsPepeTexture;

  sf::Font m_ButtonFont;

 public:
  MenuScene();
  ~MenuScene();
  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif
