#ifndef SAVESCENE_H
#define SAVESCENE_H

#include "Scene.hpp"
#include "ui/Button.hpp"

class SaveGame;
class SaveScene : public Scene {
 public:
  /**
   * SaveScene Constructor.
   */
  SaveScene(SaveGame* savegame);

  /**
   * SaveScene Destructor.
   */
  ~SaveScene();

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
   * Variable to control for marking the scene as to be popped from the game
   */
  bool m_IsKilled;

  /**
   * Go back to gamescene button
   */
  graphics::Button m_BackButton;

  /**
   * The pointer to the savegame memento created
   */
  SaveGame* m_SaveGame;

  /**
   * Buttons to display and provide selection of the slot to save to
   */
  std::vector<std::unique_ptr<graphics::Button>> m_SaveButtons;
};

#endif
