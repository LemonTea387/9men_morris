#include "MillObserver.hpp"

#include <map>
#include <vector>

#include "../GameBoard.hpp"
#include "../Tile.hpp"
namespace {

// Mills
std::vector<std::vector<TileCoord>> mills = {
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

// millLookup[TileCoord] = indices in mills that contain
// TileCoord
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
}  // namespace

void MillObserver::Notify(Tile* tileAffected) {
  const auto coord = tileAffected->GetTileCoord();
  for (const auto index : millLookup[coord]) {
    const auto a =
        m_Gameboard->GetTile(mills[index][0].first, mills[index][0].second);
    const auto b =
        m_Gameboard->GetTile(mills[index][1].first, mills[index][1].second);
    const auto c =
        m_Gameboard->GetTile(mills[index][2].first, mills[index][2].second);
    if (!a->GetToken() || !b->GetToken() || !c->GetToken()) continue;

    if (a->GetToken()->GetOccupation() == b->GetToken()->GetOccupation() &&
        b->GetToken()->GetOccupation() == c->GetToken()->GetOccupation()) {
      m_Gameboard->SetMillFlag(true);
      return;
    }
  }
}
