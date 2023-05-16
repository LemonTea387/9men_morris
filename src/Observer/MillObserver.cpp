#include "MillObserver.hpp"

#include "../GameBoardUtils.hpp"

void MillObserver::Notify(Tile* tileAffected) {
  if (Util::isMill(m_Gameboard, tileAffected)) m_Gameboard->SetMillFlag(true);
}
