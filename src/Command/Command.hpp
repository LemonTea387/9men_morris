#ifndef COMMAND_H
#define COMMAND_H

#include "../Tile.hpp"
class Command {
 public:
  typedef Tile* TilePtr;
  Command(TilePtr tile) : m_AffectedTile{tile} {};
  TilePtr GetAffectedTile() { return m_AffectedTile; };
  virtual void Execute() = 0;

 protected:
  TilePtr m_AffectedTile{nullptr};
};

#endif
