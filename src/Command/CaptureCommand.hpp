#ifndef CAPTURE_COMMAND_H
#define CAPTURE_COMMAND_H

#include "Command.hpp"

class CaptureCommand : public Command {
 public:
  virtual void Execute() override;
  CaptureCommand(TilePtr tile, Player* player);
  ~CaptureCommand();
};

#endif
