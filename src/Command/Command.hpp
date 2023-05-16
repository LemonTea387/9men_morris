#ifndef COMMAND_H
#define COMMAND_H

#include "../Player.hpp"
#include "../Tile.hpp"

class Command {
 public:
  typedef Tile* TilePtr;
  Command(TilePtr tile, Player* player)
      : m_AffectedTile{tile}, m_Player{player} {};
  TilePtr GetAffectedTile() { return m_AffectedTile; };
  virtual void Execute() = 0;

 protected:
  TilePtr m_AffectedTile{nullptr};
  Player* m_Player;
};

#endif
