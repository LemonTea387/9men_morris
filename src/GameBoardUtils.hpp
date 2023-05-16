#ifndef GAMEBOARDUTIL_H
#define GAMEBOARDUTIL_H

#include <utility>
#include <unordered_map>
#include <vector>

namespace Util {
static constexpr int ROW_MAX = 7;
typedef std::pair<int, int> TileCoord;
std::vector<TileCoord> GetNeighbours(TileCoord coord);
}  // namespace Util
#endif
