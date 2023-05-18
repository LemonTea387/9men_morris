#ifndef CREDITSSCENE_H
#define CREDITSSCENE_H

#include <SFML/Graphics.hpp>
#include <array>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"

/**
 * CreditsScene shows the credits to the developers of the game.
 */
class CreditsScene : public Scene {
 private:
  /**
   * The main title's background Rectangle
   */
  sf::RectangleShape m_TitleBackground;

  /**
   * The title text
   */
  sf::Text m_TitleText;

  /**
   * Developers
   */
  std::array<sf::Text, 3> m_Authors;

  /**
   * Return to MainMenu Button
   */
  graphics::Button m_ReturnButton;

 public:
  /**
  * CreditsScene Constructor
  */
  CreditsScene();

  /**
  * CreditsScene Destructor
  */
  ~CreditsScene();

  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif
