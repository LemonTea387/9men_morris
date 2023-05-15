#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include <memory>

#include "Scene/ui/Button.hpp"

class GameBoard;
/**
 * TO-DO: Create class for TileCoord with proper bounds checkings.
 * Can  also possibly overload the hash function () operator / equality check
 * to use std::unordered_map for a tiny bit extra performance.
 */

typedef GameBoard* GameBoardPtr;
typedef std::pair<int, int> TileCoord;

class Tile : public graphics::Button {
 public:
  enum Occupation { DOGE, PEPE, NONE };
  enum TokenState { NORMAL, SCREAM, SUNGLASSES };
  void setHorzCoords(int, int);
  void setVertCoords(int, int);
  void setOccupation(Occupation);
  void swapOccupation(Tile*);
  void setScream();
  void setNormal();
  void setSunglasses();
  bool isAdjacent(Tile*);
  Occupation getOccupation();
  TileCoord getHorzCoords();
  TileCoord getVertCoords();
  Tile(GameBoardPtr);
  ~Tile();

 private:
  GameBoardPtr m_Gameboard;
  TileCoord horizontal_coords;
  TileCoord vertical_coords;
  Occupation occupation;
  TokenState state;
};
#endif
