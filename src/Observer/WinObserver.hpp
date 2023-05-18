#ifndef WIN_OBSERVER_H
#define WIN_OBSERVER_H

#include "Observer.hpp"

/**
 * Observes a 'Win' in the GameBoard leading from a Command execution,
 * NOTE : Must be the LAST Observer to add to the GameBoard. This
 * detects the Win based on the the DEFINED gamerules for 9 Men Morris. In which
 * there can be 2 win conditions :
 * 1) Opponent has less than 3 tokens left on the board and opponent is done
 * placing tokens
 * 2) There are no valid moves for the opponent after current player's turn.
 */
class WinObserver : public Observer {
 public:
  /**
   * Only checks the tile that has changed if it will result in a Win condition
   * after a Command.
   */
  virtual void Notify(Tile* tileAffected) override;

  /**
   * WinObserver Constructor.
   */
  WinObserver(GameBoard* gb);
};
#endif
