#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

#include "Command/Command.hpp"
#include "Game.hpp"
#include "Observer/Observer.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class GameBoard {
  static constexpr float BOARD_X{554.};
  static constexpr float BOARD_Y{554.};
  static constexpr float TILE_DIM{90.};
  const float TILE_X_PAD{(Game::WINDOW_WIDTH - BOARD_X) / 2};
  const float TILE_Y_PAD{(Game::WINDOW_HEIGHT - BOARD_Y) / 2};

 public:
  enum GameState { PLACE, MOVE, CAPTURE };
  GameBoard();
  ~GameBoard();
  void SetMillFlag(bool flag);
  void Update(sf::Event event);
  void Render(sf::RenderWindow& window);
  void ExecuteCommand(Command* command);
  void SetActiveTile(Tile* tile);
  Tile* GetActiveTile();
  Tile* GetTile(int x, int y) const;
  Player* GetCurrPlayer() const;
  Player* GetOpponentPlayer();
  GameState GetState() const;

 private:
  std::array<std::array<std::unique_ptr<Tile>, 7>, 7> m_Board;
  std::vector<Observer*> m_Observers;
  sf::RectangleShape m_BoardShape;
  bool m_HasMillCapture{false};
  bool m_ProgressTurn{false};
  Tile* m_ActiveTile{nullptr};
  Player m_P1;
  Player m_P2;
  Player* m_Turn;
  GameState m_State;

  void CalculateValidMoves();
  void InitialiseTiles();
  void CancelHighlight();
};

#endif
