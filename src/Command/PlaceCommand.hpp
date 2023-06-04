#ifndef PLACE_COMMAND_H
#define PLACE_COMMAND_H
#include <memory>

#include "Command.hpp"

/**
 * PlaceCommand places a new Token into an empty Tile.
 */
class PlaceCommand : public Command {
 public:
  /**
  * Make a new Token and place it in m_AffectedTile
  */
  virtual void Execute() override;

  /**
   * Undos the placement of tile
   */
  virtual void Undo() override;

  /**
  * PlaceCommand Constructor
  */
  PlaceCommand(TilePtr tile, Player* player);

  /**
  * PlaceCommand Destructor
  */
  ~PlaceCommand();
};

#endif
