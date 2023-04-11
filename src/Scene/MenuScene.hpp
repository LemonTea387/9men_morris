#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>

#include "SFML/Graphics/RectangleShape.hpp"
#include "Scene.hpp"

class MenuScene : public Scene {
 private:
  // TO-DO: Use a Button class (with rounded corners, hover support, etc.)
  sf::RectangleShape m_QuitButton;
  sf::Text m_QuitText;
  sf::Texture m_QuitTexture;

  sf::Font m_ButtonFont;

 public:
  MenuScene();
  ~MenuScene();
  virtual void Update(sf::Event event) override;
  virtual void Render() override;
};

#endif
