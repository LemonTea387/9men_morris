#include "MillObserver.hpp"

#include "../GameBoardUtils.hpp"

MillObserver::MillObserver(GameBoard* gb) : Observer::Observer(gb) {}

void MillObserver::Notify(Tile* tileAffected) {
  // If it is a mill, communicate with the GameBoard that Mill has been formed
  if (Util::isMill(m_Gameboard, tileAffected)) m_Gameboard->SetMillFlag(true);
}
