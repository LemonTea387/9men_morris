#ifndef SAVESCENE_H
#define SAVESCENE_H

#include "Scene.hpp"
#include "ui/Button.hpp"
#include "ui/TextField.hpp"

class SaveScene : public Scene {
 private:
  graphics::Button m_SaveButton;
  graphics::Button m_MenuButton;
  sf::Text m_SaveText;
  TextField m_TextField;


 public:
  /**
   * SaveScene Constructor.
   */
  SaveScene();

  /**
   * SaveScene Destructor.
   */
  ~SaveScene();

  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif