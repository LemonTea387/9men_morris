#include "CaptureCommand.hpp"

CaptureCommand::CaptureCommand(TilePtr tile, Player* player)
    : Command::Command{tile, player} {}

void CaptureCommand::Execute() {
  m_AffectedTile->RemoveToken();
  m_Player->left--;
}
