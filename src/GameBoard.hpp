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
  void Update(sf::Event event);
  void Render(sf::RenderWindow& window);
  void ExecuteCommand(Command* command);
  void SetActiveTile(Tile* tile) {
    m_ActiveTile = tile;
    CalculateValidMoves();
  };
  Tile* GetActiveTile() { return m_ActiveTile; };
  GameState GetState() const { return m_State; };
  Player* GetCurrPlayer() const { return m_Turn; };
  Player* GetOpponentPlayer() { return &m_P1 == m_Turn ? &m_P2 : &m_P1; };
  void SetMillFlag(bool flag) { m_HasMillCapture = flag; }
  Tile* GetTile(int x, int y) const { return m_Board[x][y].get(); }

 private:
  void CalculateValidMoves();
  void InitialiseTiles();
  void CancelHighlight();
  std::array<std::array<std::unique_ptr<Tile>, 7>, 7> m_Board;
  sf::RectangleShape m_BoardShape;
  std::vector<Observer*> m_Observers;

  Player* m_Turn;
  Player m_P1;
  Player m_P2;
  bool m_HasMillCapture{false};
  bool m_ProgressTurn{false};
  Tile* m_ActiveTile{nullptr};
  GameState m_State;
};

#endif
