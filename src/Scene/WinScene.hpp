#ifndef WINSCENE_H
#define WINSCENE_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"

/**
 * Ideally, should be dependent on the amount of Token Occupations, but there is
 * possibly a TIE condition.
 */
enum WinnerType { DOGE, PEPE, TIE };

/**
 * The Scene showed after the game has been won/tie. Reacts to the player that
 * won if a win happens.
 */
class WinScene : public Scene {
 private:
  /**
   * Return to Menu button
   */
  graphics::Button m_MenuButton;

  /**
   * The image displayed depending on the WinnerType
   */
  sf::RectangleShape m_WinImage;

  /**
   * The message displayed depending on the WinnerType
   */
  sf::Text m_WinMessage;

 public:
  /**
   * WinScene Constructor, takes in a WinnerType to show the scene based on the
   * WinnerType.
   */
  WinScene(WinnerType wt);

  /**
  * WinScene Destructor.
  */
  ~WinScene();

  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif
