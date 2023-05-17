#ifndef OBSERVER_H
#define OBSERVER_H

#include "../Tile.hpp"

class Observer {
 public:
  Observer(GameBoard* gameboard) : m_Gameboard{gameboard} {};
  ~Observer() = default;
  virtual void Notify(Tile* tileAffected) = 0;

 protected:
  GameBoard* m_Gameboard;
};
#endif