#include "MoveCommand.hpp"

MoveCommand::MoveCommand(TilePtr srcTile, TilePtr dstTile, Player* player)
    : Command::Command(dstTile, player), m_SrcTile{srcTile} {}

MoveCommand::~MoveCommand() {}

void MoveCommand::Execute() {
  // Check to see if source Tile is valid and it has tokens.
  if (!m_SrcTile || !(m_SrcTile->HasToken())) return;
  m_SrcTile->MoveToken(m_AffectedTile);
}
