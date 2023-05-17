#ifndef WIN_OBSERVER_H
#define WIN_OBSERVER_H

#include "Observer.hpp"

class WinObserver : public Observer {
 public:
  virtual void Notify(Tile* tileAffected) override;
  WinObserver(GameBoard* gb);
};
#endif
