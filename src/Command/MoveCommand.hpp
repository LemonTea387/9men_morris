#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.hpp"

/**
 * MoveCommand is a command that moves a Token from a Tile to another empty
 * Tile.
 */
class MoveCommand : public Command {
 public:
  /**
   * Moves a Token to another Tile.
   */
  virtual void Execute() override;

  /**
   * Undo this MoveCommand
   */
  virtual void Undo() override;

  /**
   * MoveCommand Constructor, srcTile is the tile to move the token from, and
   * dstTile is the destination to move to.
   */
  MoveCommand(TilePtr srcTile, TilePtr dstTile, Player* player);

  /**
   * MoveCommand Destructor.
   */
  ~MoveCommand();

  virtual void AddToSaveGame(SaveGamePtr) override;
  virtual void RestoreFromSave(std::string save) override;

 private:
  /**
   * The Tile to move tokens from.
   */
  TilePtr m_SrcTile;
};
#endif
