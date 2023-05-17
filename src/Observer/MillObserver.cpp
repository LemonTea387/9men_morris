#include "MillObserver.hpp"

#include "../GameBoardUtils.hpp"

MillObserver::MillObserver(GameBoard* gb) : Observer::Observer(gb) {}

void MillObserver::Notify(Tile* tileAffected) {
  if (Util::isMill(m_Gameboard, tileAffected)) m_Gameboard->SetMillFlag(true);
}
