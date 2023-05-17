#ifndef MILLOBSERVER_H
#define MILLOBSERVER_H

#include "Observer.hpp"
#include "../GameBoard.hpp"
#include "../Tile.hpp"

class MillObserver : public Observer {
 private:
 public:
  virtual void Notify(Tile* tileAffected) override;
  MillObserver(GameBoard* gb);
};
#endif
