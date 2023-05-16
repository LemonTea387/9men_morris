#ifndef PLACE_COMMAND_H
#define PLACE_COMMAND_H
#include <memory>

#include "Command.hpp"

class PlaceCommand : public Command {
 public:
  virtual void Execute() override;
  PlaceCommand(TilePtr tile, Player* player);
  ~PlaceCommand();
};

#endif
