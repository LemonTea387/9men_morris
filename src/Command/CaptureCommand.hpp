#ifndef CAPTURE_COMMAND_H
#define CAPTURE_COMMAND_H

#include <memory>

#include "../Token.hpp"
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
   * Undos the capture and returns the token to the tile
   */
  virtual void Undo() override;

  /**
   * Serialises the capture command and adds to the SaveGame memento
   */
  virtual void AddToSaveGame(SaveGamePtr) override;

  /**
   * Deserialises the string into a CaptureCommand
   */
  virtual void RestoreFromSave(std::string save, GameBoard* gb) override;

  /**
   * Capture Command's Constructor, the player pointer here is actually the
   * player getting captured, NOT the player initiating the capture.
   */
  CaptureCommand(TilePtr tile, Player* player);
  ~CaptureCommand();

 private:
  std::unique_ptr<Token> m_CapturedToken{nullptr};
};

#endif
