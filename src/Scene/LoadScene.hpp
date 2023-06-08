#ifndef LOADSCENE_H
#define LOADSCENE_H

#include "Scene.hpp"
#include "ui/Button.hpp"

class LoadScene : public Scene {
 public:
  /**
   * LoadScene Constructor.
   */
  LoadScene();

  /**
   * LoadScene Destructor.
   */
  ~LoadScene();

  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;

 private:
  /**
   * The background rectangle for the title.
   */
  sf::RectangleShape m_TitleBackground;
  /**
   * Main Title's text
   */
  sf::Text m_TitleText;

  /**
   * Variable to control for marking the scene as to be popped from the game.
   */
  bool m_IsKilled;

  /**
   * String for the filename of the save selected
   */
  std::string m_SaveFilename;

  /**
   * Go back to main menu button
   */
  graphics::Button m_MenuButton;

  /**
   * Buttons to display and provide selection of game saves.
   */
  std::vector<std::unique_ptr<graphics::Button>> m_LoadButtons;
};

#endif
