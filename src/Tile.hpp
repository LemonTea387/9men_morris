#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

namespace Tile {

/**
 * TO-DO: Create class for TileCoord with proper bounds checkings.
 * Can  also possibly overload the hash function () operator / equality check
 * to use std::unordered_map for a tiny bit extra performance.
 */
typedef std::pair<int, int> TileCoord;

enum class Occupation { DOGE, PEPE, NONE };

struct Tile {
  /**
   * Position withing screen space.
   */
  sf::Vector2f coords;
  /**
   * Position within the "Game Board"
   */
  TileCoord position;
  Occupation occupation;
};

}  // namespace Tile
#endif
