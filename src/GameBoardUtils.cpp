#include "GameBoardUtils.hpp"

#include <map>
#include <unordered_map>

namespace Util {
// TODO: Automatic generation of this
/**
 * Adjacency list of each tile.
 * Current implementation uses pre-computed values, this is a trade-off we
 * agreed that we want a O(1) lookup and fastest possible generation of such
 * tables O(1) with the cost of certain inflexibilities and some memory for
 * storing the table.
 * unordered_map does not support std::pair hashing, so it is converted to a
 * singular int.
 */
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

/**
 * All the Mills in the gameboard.
 * Current implementation uses pre-computed values, this is a trade-off we
 * agreed that we want a O(1) lookup and fastest possible generation of such
 * tables O(1) with the cost of certain inflexibilities and some memory for
 * storing the table
 *
 */
std::vector<TileCoordVector> mills = {
    // Horizontal Mills
    {{0, 0}, {3, 0}, {6, 0}},

    {{1, 1}, {3, 1}, {5, 1}},

    {{2, 2}, {3, 2}, {4, 2}},

    {{0, 3}, {1, 3}, {2, 3}},
    {{4, 3}, {5, 3}, {6, 3}},

    {{2, 4}, {3, 4}, {4, 4}},

    {{1, 5}, {3, 5}, {5, 5}},

    {{0, 6}, {3, 6}, {6, 6}},

    // Vertical Mills

    {{0, 0}, {0, 3}, {0, 6}},

    {{1, 1}, {1, 3}, {1, 5}},

    {{2, 2}, {2, 3}, {2, 4}},

    {{3, 0}, {3, 1}, {3, 2}},
    {{3, 4}, {3, 5}, {3, 6}},

    {{4, 2}, {4, 3}, {4, 4}},

    {{5, 1}, {5, 3}, {5, 5}},

    {{6, 0}, {6, 3}, {6, 6}},
};

/**
 * millLookup[TileCoord] = indices in mills that contain
 * Lookup the mills table above to get the mills that contains this tile.
 * Current implementation uses pre-computed values, this is a trade-off we
 * agreed that we want a O(1) lookup and fastest possible generation of such
 * tables O(1) with the cost of certain inflexibilities and some memory for
 * storing the table
 */
std::map<TileCoord, std::vector<int>> millLookup = {
    {{0, 0}, {0, 8}},  {{3, 0}, {0, 11}}, {{6, 0}, {0, 15}},

    {{1, 1}, {1, 9}},  {{3, 1}, {1, 11}}, {{5, 1}, {1, 14}},

    {{2, 2}, {2, 10}}, {{3, 2}, {2, 11}}, {{4, 2}, {2, 13}},

    {{0, 3}, {3, 8}},  {{1, 3}, {3, 9}},  {{2, 3}, {3, 10}},

    {{4, 3}, {4, 13}}, {{5, 3}, {4, 14}}, {{6, 3}, {4, 15}},

    {{2, 4}, {5, 10}}, {{3, 4}, {5, 12}}, {{4, 4}, {5, 13}},

    {{1, 5}, {6, 9}},  {{3, 5}, {6, 12}}, {{5, 5}, {6, 14}},

    {{0, 6}, {7, 8}},  {{3, 6}, {7, 12}}, {{6, 6}, {7, 15}},
};

TileCoordVector GetNeighbours(TileCoord coord) {
  return adjacents[coord.first + coord.second * ROW_MAX];
};

std::vector<TileCoordVector> GetMillOfCoord(TileCoord coord) {
  std::vector<TileCoordVector> millOfCoord{};
  for (const auto index : millLookup[coord]) {
    millOfCoord.push_back(mills[index]);
  }
  return millOfCoord;
};

bool isMill(const GameBoard* gameboard, const Tile* tile) {
  const auto coord = tile->GetTileCoord();
  for (const auto mill : GetMillOfCoord(coord)) {
    // Checking if the 3 Tiles in the mill has tokens and the saem occupation.
    const auto a = gameboard->GetTile(mill[0].first, mill[0].second);
    const auto b = gameboard->GetTile(mill[1].first, mill[1].second);
    const auto c = gameboard->GetTile(mill[2].first, mill[2].second);

    Token* token_a = a->GetToken();
    Token* token_b = b->GetToken();
    Token* token_c = c->GetToken();

    if (!token_a || !token_b || !token_c) continue;

    Token::Occupation occupation_a = token_a->GetOccupation();
    Token::Occupation occupation_b = token_b->GetOccupation();
    Token::Occupation occupation_c = token_c->GetOccupation();

    if (occupation_a == occupation_b && occupation_b == occupation_c) {
      return true;
    }
  }
  return false;
}

}  // namespace Util
