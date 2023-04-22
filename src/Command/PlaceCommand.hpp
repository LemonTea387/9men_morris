#ifndef PLACE_COMMAND_H
#define PLACE_COMMAND_H
#include <memory>

#include "../Tile.hpp"
#include "Command.hpp"

class GameBoard;
class PlaceCommand : public Command {
 private:
  // Needs to be a shared_ptr because this Command class
  // isn't going to take ownership of the GameBoard pointer.
  typedef std::shared_ptr<GameBoard> GameBoardPtr;

  GameBoardPtr m_GameBoard;
  Tile::Tile m_ToPlace;

 public:
  virtual void execute() override;
  PlaceCommand(GameBoardPtr, Tile::Tile);
  ~PlaceCommand();
};

#endif
