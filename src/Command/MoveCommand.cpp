#include "MoveCommand.hpp"

MoveCommand::MoveCommand(TilePtr srcTile, TilePtr dstTile, Player* player)
    : Command::Command(dstTile, player), m_SrcTile{srcTile} {}

MoveCommand::~MoveCommand() {}

void MoveCommand::Execute() {
  // Check to see if source Tile is valid and it has tokens.
  if (!m_SrcTile || !(m_SrcTile->HasToken())) return;
  m_SrcTile->MoveToken(m_AffectedTile);
}

void MoveCommand::Undo() { m_AffectedTile->MoveToken(m_SrcTile); }
void MoveCommand::AddToSaveGame(SaveGamePtr) {}
Command* MoveCommand::RestoreFromSave(std::string save) {
  return new MoveCommand(this->m_SrcTile, this->m_AffectedTile, this->m_Player);
}
