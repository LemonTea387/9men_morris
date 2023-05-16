#include "PlaceCommand.hpp"

#include <memory>

#include "../Token.hpp"

void PlaceCommand::Execute() {
  m_AffectedTile->SetToken(std::move(std::make_unique<Token>(
      m_Player->occupation, m_AffectedTile->getPosition())));
  m_Player->placed++;
}

PlaceCommand::PlaceCommand(TilePtr tile, Player* player)
    : Command::Command(tile, player) {}

PlaceCommand::~PlaceCommand() {}
