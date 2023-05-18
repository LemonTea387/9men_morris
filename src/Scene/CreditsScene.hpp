#ifndef CREDITSSCENE_H
#define CREDITSSCENE_H

#include <SFML/Graphics.hpp>
#include <array>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"

class CreditsScene : public Scene {
 private:
  sf::RectangleShape m_TitleBackground;
  sf::Text m_TitleText;

  std::array<sf::Text, 3> m_Authors;

  graphics::Button m_ReturnButton;

 public:
  CreditsScene();
  ~CreditsScene();
  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif
