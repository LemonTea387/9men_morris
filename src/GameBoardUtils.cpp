#include "GameBoardUtils.hpp"

namespace Util {
// TODO: Automatic generation of this
std::unordered_map<int, std::vector<TileCoord>> adjacents = {
    {0 + ROW_MAX * 0, {{3, 0}, {0, 3}}},
    {3 + ROW_MAX * 0, {{0, 0}, {3, 1}, {6, 0}}},
    {6 + ROW_MAX * 0, {{3, 0}, {6, 3}}},

    {1 + ROW_MAX * 1, {{3, 1}, {1, 3}}},
    {3 + ROW_MAX * 1, {{1, 1}, {3, 0}, {5, 1}, {3, 2}}},
    {5 + ROW_MAX * 1, {{3, 1}, {5, 3}}},

    {2 + ROW_MAX * 2, {{3, 2}, {2, 3}}},
    {3 + ROW_MAX * 2, {{2, 2}, {3, 1}, {4, 2}}},
    {4 + ROW_MAX * 2, {{3, 2}, {4, 3}}},

    {0 + ROW_MAX * 3, {{0, 0}, {1, 3}, {0, 6}}},
    {1 + ROW_MAX * 3, {{1, 1}, {2, 3}, {1, 5}, {0, 3}}},
    {2 + ROW_MAX * 3, {{2, 2}, {2, 4}, {1, 3}}},
    {4 + ROW_MAX * 3, {{4, 2}, {5, 3}, {4, 4}}},
    {5 + ROW_MAX * 3, {{5, 1}, {6, 3}, {5, 5}, {4, 3}}},
    {6 + ROW_MAX * 3, {{6, 0}, {6, 6}, {5, 3}}},

    {2 + ROW_MAX * 4, {{3, 4}, {2, 3}}},
    {3 + ROW_MAX * 4, {{2, 4}, {3, 5}, {4, 4}}},
    {4 + ROW_MAX * 4, {{3, 4}, {4, 3}}},

    {1 + ROW_MAX * 5, {{3, 5}, {1, 3}}},
    {3 + ROW_MAX * 5, {{1, 5}, {3, 4}, {5, 5}, {3, 6}}},
    {5 + ROW_MAX * 5, {{3, 5}, {5, 3}}},

    {0 + ROW_MAX * 6, {{3, 6}, {0, 3}}},
    {3 + ROW_MAX * 6, {{0, 6}, {3, 5}, {6, 6}}},
    {6 + ROW_MAX * 6, {{3, 6}, {6, 3}}},
};
std::vector<TileCoord> GetNeighbours(TileCoord coord) {
  return adjacents[coord.first + coord.second * ROW_MAX];
};
}  // namespace Util
