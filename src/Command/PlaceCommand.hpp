#ifndef PLACE_COMMAND_H
#define PLACE_COMMAND_H
#include <memory>

#include "../Tile.hpp"
#include "Command.hpp"

class PlaceCommand : public Command {
 public:
  virtual void Execute() override;
  PlaceCommand(TilePtr tile, Token::Occupation occupation);
  ~PlaceCommand();
 private:
  Token::Occupation m_Occupation;
};

#endif
