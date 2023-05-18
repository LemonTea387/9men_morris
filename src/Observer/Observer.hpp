#ifndef OBSERVER_H
#define OBSERVER_H

#include "../Tile.hpp"

/**
 * Observes the GameBoard for any changes from a Command that may lead to a new
 * gameplay state or progression. This is used for detecting any game rule such
 * as Mill formation in the GameBoard. Needs to be Notify() after every Command
 * from GameBoard.
 */
class Observer {
 public:
  /**
   * Observer Constructor, the gameboard here refers to the gameboard the
   * Observer is observing on.
   */
  Observer(GameBoard* gameboard) : m_Gameboard{gameboard} {};

  /**
   * Observer Destructor.
   */
  ~Observer() = default;

  /**
   * Used to notify the observer with the Tile that's affected.
   */
  virtual void Notify(Tile* tileAffected) = 0;

 protected:
  /**
   * GameBoard tha the observer observes.
   */
  GameBoard* m_Gameboard;
};
#endif
