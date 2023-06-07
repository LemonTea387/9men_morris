#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../Token.hpp"
#include "Scene.hpp"
#include "ui/Button.hpp"
class GameBoard;

/**
 * The Scene for the gameplay. GameScene creates a game with GameBoard and
 * allows playing of the game.
 */
class GameScene : public Scene {
 private:
  /**
   * Updates the Text and Icon to show the name and icon of the current turn's
   * Player icon and name.
   */
  void UpdateTextAndIcons();

  /**
   * Stores the Previous turn the gameboard has played, this is to keep track of
   * the changes to the turns which if no change to turn we would not have to
   * perform an expensive texture change when displaying turns.
   */
  Token::Occupation m_PrevTurn;

  /**
   * Button to Quit to previous Scene.
   */
  graphics::Button m_QuitButton;

  /**
   * Button to Save the game.
   */
  graphics::Button m_SaveButton;

  /**
   * Button to Save the game.
   */
  graphics::Button m_UndoButton;

  /**
   * Labels the Icon of Player 1
   */
  sf::Text m_PlayerOneText;

  /**
   * Labels the Icon of Player 2
   */
  sf::Text m_PlayerTwoText;

  /**
   * Text for displaying the current turn (player), and the current action.
   */
  sf::Text m_TurnText;

  /**
   * Icon of Player 1
   */
  sf::RectangleShape m_PlayerOneIcon;

  /**
   * Icon of Player 2
   */
  sf::RectangleShape m_PlayerTwoIcon;

  /**
   * The current turn's (player) icon.
   */
  sf::RectangleShape m_TurnIcon;

  /**
   * Player 1's texture, for ease of swapping textures for m_TurnIcon
   */
  sf::Texture* m_PlayerOneTexture;

  /**
   * Player 2' texture, for ease of swapping textures for m_TurnIcon
   */
  sf::Texture* m_PlayerTwoTexture;

  /**
   * The GameBoard that the game is played.
   */
  std::unique_ptr<GameBoard> m_GameBoard;

 public:
  /**
   * GameScene Constructor.
   */
  GameScene();

  /**
   * GameScene Constructor from a Savegame file.
   */
  GameScene(const std::string& savegame);

  /**
   * GameScene Destructor.
   */
  ~GameScene();

  virtual void Update(sf::Event event) override;
  virtual void Render(sf::RenderWindow& window) override;
};

#endif
