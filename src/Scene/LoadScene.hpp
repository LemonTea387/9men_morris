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

  bool m_IsKilled;
  graphics::Button m_MenuButton;
  std::vector<std::unique_ptr<graphics::Button>> m_LoadButtons;
};

#endif
