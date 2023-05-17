#ifndef CAPTURE_COMMAND_H
#define CAPTURE_COMMAND_H

#include "Command.hpp"

/**
 * The CaptureCommand is a command to capture the affected player's(opponent of
 * the current turn) token
 */
class CaptureCommand : public Command {
 public:
  /**
   * Captures the affected player's token (removes it from Tile).
   */
  virtual void Execute() override;
  /**
   * Capture Command's Constructor, the player pointer here is actually the
   * player getting captured, NOT the player initiating the capture.
   */
  CaptureCommand(TilePtr tile, Player* player);
  ~CaptureCommand();
};

#endif
