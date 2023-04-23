#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "Scene/ui/Button.hpp"

namespace Tile {

/**
 * TO-DO: Create class for TileCoord with proper bounds checkings.
 * Can  also possibly overload the hash function () operator / equality check
 * to use std::unordered_map for a tiny bit extra performance.
 */
typedef std::pair<int, int> TileCoord;

enum class Occupation { DOGE, PEPE, NONE };

class Tile: public graphics::Button {
 private:
  TileCoord horizontal_coords;
  TileCoord vertical_coords;
  Occupation occupation;

 public:
  Tile();
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
