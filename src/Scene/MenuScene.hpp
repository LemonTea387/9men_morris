#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <SFML/Graphics.hpp>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"

/**
 * Scene for showing main menu. This scene is the main menu of the game, and is
 * supposed to be the 'hub' of the application and thus the first scene. Users
 * should have ways to navigate from MenuScene to ideally all non-trivial Scenes
 * used in the Application.
 */
class MenuScene : public Scene {
 private:
  /**
   * Small Image for the game.
   */
  sf::RectangleShape m_DogeVsPepe;

  /**
   * The background rectangle for the title.
   */
  sf::RectangleShape m_TitleBackground;
  /**
   * Main Title's text
   */
  sf::Text m_TitleText;

  /**
   * Copyright notice text
   */
  sf::Text m_CopyrightNotice;

  /**
   * Copyright holder text
   */
  sf::Text m_CopyrightHolder;

  /**
   * Button to start a new game.
   */
  graphics::Button m_NewGameButton;

  /**
   * Button to load a saved game.
   */
  graphics::Button m_LoadGameButton;

  /**
   * Button to show credits.
   */
  graphics::Button m_CreditsButton;

  /**
   * Button to exit game.
   */
  graphics::Button m_ExitButton;

 public:
  /**
  * MenuScene Constructor
  */
  MenuScene();

  /**
  * MenuScene Destructor
  */
  ~MenuScene();

  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif
