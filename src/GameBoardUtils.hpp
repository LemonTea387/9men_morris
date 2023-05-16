#ifndef GAMEBOARDUTIL_H
#define GAMEBOARDUTIL_H

#include <utility>
#include <vector>

#include "GameBoard.hpp"
#include "Tile.hpp"

namespace Util {
static constexpr int ROW_MAX = 7;
typedef std::pair<int, int> TileCoord;
typedef std::vector<TileCoord> TileCoordVector;

TileCoordVector GetNeighbours(TileCoord coord);
std::vector<TileCoordVector> GetMillOfCoord(TileCoord coord);
// TODO: can it not have tiles?
bool isMill(const GameBoard* gameboard, const Tile* tile);
}  // namespace Util
#endif
