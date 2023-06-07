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

  bool m_IsKilled;
  graphics::Button m_MenuButton;
  SaveGame* m_SaveGame;
  std::vector<std::unique_ptr<graphics::Button>> m_SaveButtons;
};

#endif
