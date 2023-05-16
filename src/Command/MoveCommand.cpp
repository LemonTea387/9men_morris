#include "MoveCommand.hpp"

MoveCommand::MoveCommand(TilePtr srcTile, TilePtr dstTile) : Command::Command(dstTile), m_SrcTile{srcTile}{}

void MoveCommand::Execute() {
  if(!m_SrcTile || !(m_SrcTile->HasToken())) return;
  m_SrcTile->MoveToken(m_AffectedTile);
}
