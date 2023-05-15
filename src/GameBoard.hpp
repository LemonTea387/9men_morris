#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

#include "Tile.hpp"

enum class GameState { PLACE, MOVE, CAPTURE, FLY };

class GameBoard {
 public:
  void Update(sf::Event event);
  void Render(sf::RenderWindow& window);
  GameBoard();
  ~GameBoard();
  void Notify(Tile*);

 private:
  std::array<std::array<std::unique_ptr<Tile>, 3>, 8> horz_board;
  std::array<std::array<Tile*, 3>, 8> vert_board;
  std::array<std::array<std::unique_ptr<Tile>, 8>, 8> m_board;
  sf::RectangleShape m_BoardShape;
  sf::Texture m_BoardTexture;
  std::vector<Tile*> tile_q;
  Tile* curr_tile;
  void InitialiseTiles();

  int p1_placed;
  int p2_placed;
  int p1_left;
  int p2_left;
  Tile::Occupation turn;
  GameState curr_state;
  void nextRound();

  bool isWin();
  bool isMill();

  void place();
  void move();
  void fly();
  void capture();
  void switch_turn();

  friend class GameScene;
};

#endif
