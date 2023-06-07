#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include <stack>
#include <vector>

#include "Command/Command.hpp"
#include "Game.hpp"
#include "Observer/Observer.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class SaveGame;

/**
 * GameBoard is the representation of the 9 Men's Morris gameboard, it is
 * responsible for the 9 Men's Morris game to run. The GameBoard handles
 * internally the running and handling of the game, as long as Render is called
 * to draw the GameBoard, and Update is called to pass down the window context
 * events (sf::Event) to the GameBoard, it will know how and when to progress
 * the game without other intervention.
 */
class GameBoard {
  /**
   * Board Dimensions in Pixels
   */
  static constexpr float BOARD_X{554.};
  static constexpr float BOARD_Y{554.};

  /**
   * Dimension for each Tile, tiles are perfect squares.
   */
  static constexpr float TILE_DIM{90.};

  /**
   * Paddings for left and top for initial placements of the tile.
   */
  const float TILE_X_PAD{(Game::WINDOW_WIDTH - BOARD_X) / 2};
  const float TILE_Y_PAD{(Game::WINDOW_HEIGHT - BOARD_Y) / 2 - 50};

 public:
  /**
   * The phase the gameboard is in, dictates the action the current player does
   */
  enum GameState { PLACE, MOVE, CAPTURE };

  /**
   * GameBoard Constructor, makes an empty gameboard.
   */
  GameBoard();

  /**
   * GameBoard Destructor.
   */
  ~GameBoard();

  /**
   * Update function for Scenes to pass down the sf::Event and thus progress the
   * internal game.
   */
  void Update(sf::Event event);

  /**
   * Render function for Scenes to render(draw) the gameboard representation
   * onto the RenderWindow context.
   */
  void Render(sf::RenderWindow& window);

  /**
   * GameBoard executes the Command passed in, it will also notify the internal
   * observers on the executed Command.
   */
  void ExecuteCommand(Command* command);

  /**
   * GameBoard undos the previous Command passed in, it will also notify the
   * internal observers for preparing the state of previous command.
   */
  void UndoCommand();

  /**
   * Calculates all the valid moves using the board with for a given state, turn
   * of the player, and if any tile is selected as activeTile. activeTile is for
   * any moves that involves a source tile, such as a move of a token to another
   * Tile.
   */
  std::vector<Tile*> CalculateValidMoves(GameState state, Player* turn,
                                         Tile* activeTile);

  /**
   * Sets the current GameBoard's active tile, used for moves like moving a
   * token to another tile.
   */
  void SetActiveTile(Tile* tile);

  /**
   * Get the current m_ActiveTile for the GameBoard.
   */
  Tile* GetActiveTile();

  /**
   * Get the Tile at the coordinate (x,y), if Tile does not exist, it returns a
   * nullptr.
   */
  Tile* GetTile(int x, int y) const;

  /**
   * Returns all the Tiles that contain the Tokens of a specific player.
   */
  std::vector<Tile*> GetPlayerTiles(Player* player);

  /**
   * Sets the MillFlag for gameboard, this signals the gameboard that there is a
   * Mill formation and GameBoard needs to handle this information internally.
   */
  void SetMillFlag(bool flag);

  /**
   * Get the current turn's Player.
   */
  Player* GetCurrPlayer();

  /**
   * Get the current turn's Opponent.
   */
  Player* GetOpponentPlayer();

  /**
   * Get the current GameState of the Gameboard.
   */
  GameState GetState() const;

  /**
   * Get information on the MillFlag internally in GameBoard, this can be useful
   * to things like WinObserver.
   */
  bool GetHasMillCapture() const;

 private:
  /**
   * Board representation, current one uses 7x7 matrix with empty tiles just
   * having nullptr set.
   */
  std::array<std::array<std::unique_ptr<Tile>, 7>, 7> m_Board;

  /**
   * All the Observer bound to the GameBoard
   */
  std::vector<std::unique_ptr<Observer>> m_Observers;

  /**
   * The Command history of this current game.
   */
  std::stack<std::unique_ptr<Command>> m_CommandsHistory;

  /**
   * The main GameBoard texture is drawn on this RectangleShape
   */
  sf::RectangleShape m_BoardShape;

  /**
   * Flag for signaling a Mill Formation.
   */
  bool m_HasMillCapture{false};

  /**
   * Flag for signaling a Command has just been executed and GameBoard needs to
   * prepare for the next turn.
   */
  bool m_ProgressTurn{false};

  /**
   * Current selected tile, this is useful for moves that is initiated with 2
   * tiles.
   */
  Tile* m_ActiveTile{nullptr};

  /**
   * Player 1 playing the game.
   */
  Player m_P1;

  /**
   * Player 2 playing the game.
   */
  Player m_P2;

  /**
   * Current turn's player.
   */
  Player* m_Turn;

  /**
   * The current phase the game of 9 Men's Morris is in.
   */
  GameState m_State;

  /**
   * The shape of the Doge Tokens left to be placed.
   */
  sf::RectangleShape m_DogeTokenLeft;
  /**
   * The shape of the Pepe Tokens left to be placed.
   */
  sf::RectangleShape m_PepeTokenLeft;

  /**
   * Just a simple Shader to adjust transparency. May extend
   * in the future for fancier effects
   */
  sf::Shader m_TokenLeftShader;

  /**
   * Internal Helper function for creation of the Tiles.
   */
  void InitialiseTiles();

  /**
   * Internal Helper function for asking to highlight the valid moves of the
   * current m_Turn.
   */
  void HighlightValidMoves();

  /**
   * Cancels all the highlighting of the Tiles.
   */
  void CancelHighlight();

  /**
   * Progresses the turn, which changes the game state and conditionally turn.
   */
  void ProgressTurn(bool reverse = false);

  /**
   * SaveGame file of the current game.
   */
  std::unique_ptr<SaveGame> m_SaveGame;
};

#endif
