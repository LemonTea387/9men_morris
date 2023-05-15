#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

#include "Command/Command.hpp"
#include "Game.hpp"
#include "Tile.hpp"
#include "Observer/Observer.hpp"

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
  void Placed(Token::Occupation occupation);
  GameState GetState() const { return m_State; };
  Token::Occupation GetCurrTurn() const {return m_Turn;};
  void SetMillFlag(bool flag) { m_HasMill = flag; }
  Tile* GetTile(int x, int y) const {return m_Board[x][y].get();}
  

 private:
  std::array<std::array<std::unique_ptr<Tile>, 7>, 7> m_Board;
  sf::RectangleShape m_BoardShape;
  void InitialiseTiles();
  std::vector<Observer*> m_Observers;

  Token::Occupation m_Turn{Token::Occupation::PEPE};
  bool m_HasMill{false};
  bool m_ProgressTurn{false};
  int m_P1Placed{0};
  int m_P2Placed{0};
  int m_P1Left{9};
  int m_P2Left{9};
  GameState m_State;
};

#endif
