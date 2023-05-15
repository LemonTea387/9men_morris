#ifndef MILLOBSERVER_H
#define MILLOBSERVER_H

#include "Observer.hpp"

class MillObserver : public Observer {
private:
public:
virtual void Notify(Tile* tileAffected) override;
MillObserver(GameBoard* gb): Observer::Observer(gb){

}
};
#endif