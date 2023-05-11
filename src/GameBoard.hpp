#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

namespace Tile {
class Tile;
typedef std::pair<int, int> TileCoord;
enum class Occupation { DOGE, PEPE, NONE };
}  // namespace Tile

enum class GameState { PLACE, MOVE, CAPTURE, FLY };

class GameBoard {
 private:
  std::array<std::array<std::unique_ptr<Tile::Tile>, 3>, 8> horz_board;
  std::array<std::array<std::unique_ptr<Tile::Tile>, 3>, 8> vert_board;
  sf::RectangleShape m_Board;
  sf::Texture m_BoardTexture;
  std::vector<Tile::Tile*> tile_q;
  Tile::Tile* curr_tile;
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

  //bool isWin(int);
  //bool isMill(int, Tile::Tile*);

 public:
  void Update(sf::Event event);
  void Render();
  GameBoard();
  ~GameBoard();
  // void Notified(Tile::TileCoord);
  void Notify(Tile::Tile*);

  friend class GameScene;
};

#endif
