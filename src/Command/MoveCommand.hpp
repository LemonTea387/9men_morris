#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.hpp"

class MoveCommand : public Command {
 public:
  virtual void Execute() override;
  MoveCommand(TilePtr srcTile, TilePtr dstTile);
  ~MoveCommand();

 private:
  TilePtr m_SrcTile;
};
#endif
