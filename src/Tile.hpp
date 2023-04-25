#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include <memory>

#include "Communicator.hpp"
#include "GameBoard.hpp"
#include "Scene/ui/Button.hpp"
class GameBoard;

namespace Tile {

/**
 * TO-DO: Create class for TileCoord with proper bounds checkings.
 * Can  also possibly overload the hash function () operator / equality check
 * to use std::unordered_map for a tiny bit extra performance.
 */
typedef std::pair<int, int> TileCoord;

enum class Occupation { DOGE, PEPE, NONE };

class Tile : public graphics::Button {
 private:
  typedef GameBoard* GameBoardPtr;
  GameBoardPtr m_Gameboard;
  TileCoord horizontal_coords;
  TileCoord vertical_coords;
  Occupation occupation;

 public:
  void setHorzCoords(int, int);
  void setVertCoords(int, int);
  void setOccupation(Occupation);
  void swapOccupation(Tile*);
  bool contains(int, int);
  bool isAdjacent(Tile*);
  Occupation getOccupation();
  TileCoord getHorzCoords();
  TileCoord getVertCoords();
  Tile(GameBoardPtr);
  ~Tile();
};

/**
struct Tile {
  /**
   * Position withing screen space.
   *
  sf::Vector2f screen_coords;
  /**
   * Position within the "Game Board"
   *
  TileCoord position;
  Occupation occupation;
};
*/

}  // namespace Tile
#endif
