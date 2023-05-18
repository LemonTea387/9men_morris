#ifndef MILLOBSERVER_H
#define MILLOBSERVER_H

#include "Observer.hpp"

/**
 * Observes a Mill formation of the GameBoard based on the last affected Tile.
 * After observation of a mill formation, it should communicate to the GameBoard
 * that a Mill has occured and the current player has to go into CAPTURE mode.
 */
class MillObserver : public Observer {
 public:
  /**
   * Checks if the recently affected tile has formed a Mill or not.
   */
  virtual void Notify(Tile* tileAffected) override;

  /**
   * MillObserver Constructor.
   */
  MillObserver(GameBoard* gb);
};
#endif
