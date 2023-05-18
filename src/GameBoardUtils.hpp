#ifndef GAMEBOARDUTIL_H
#define GAMEBOARDUTIL_H

#include <utility>
#include <vector>

#include "GameBoard.hpp"
#include "Tile.hpp"

/**
 * The utils to be used for all the calculations that are dependent on the
 * game's parameters like boardsize. Ideally this should be the only place that
 * needs changing for when game's parameters change.
 */
namespace Util {
/**
 * A row can have 7 tiles at max. In practice of a 9MM game it does not happen.
 */
static constexpr int ROW_MAX = 7;
typedef std::pair<int, int> TileCoord;
typedef std::vector<TileCoord> TileCoordVector;

/**
 * Get all the neighbours in coordinates of a particular coordinate of the tile
 * passed in.
 */
TileCoordVector GetNeighbours(TileCoord coord);

/**
 * Get all the Mills (includes the Tile passed in itself.) that are associated
 * to the Tile passed in as coordinates.
 */
std::vector<TileCoordVector> GetMillOfCoord(TileCoord coord);

/**
 * Checks if that tile forms a mill. This function is under consideration of
 * removal, as this utils should ideally not have dependencies on GameBoard and
 * Tile. As a substitute, the use of GetMillOfCoord() should be encouraged for
 * manual checking of Mill formations or 'is it in a Mill'.
 */
bool isMill(const GameBoard* gameboard, const Tile* tile);
}  // namespace Util
#endif
