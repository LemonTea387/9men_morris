#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "Scene/ui/Button.hpp"
#include "communicator.hpp"

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
  TileCoord horizontal_coords;
  TileCoord vertical_coords;
  Occupation occupation;

 public:
  Tile();
  ~Tile();
  void set_horizontal_coords(int, int);
  void set_vertical_coords(int, int);
  Occupation get_occupation();
  void set_occupation(Occupation);
  TileCoord get_horizontal_coords();
  TileCoord get_vertical_coords();
  bool contains(int, int);
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
