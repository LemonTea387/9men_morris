#include "CaptureCommand.hpp"

CaptureCommand::CaptureCommand(TilePtr tile, Player* player)
    : Command::Command{tile, player} {}

CaptureCommand::~CaptureCommand() {}

void CaptureCommand::Execute() {
  m_AffectedTile->RemoveToken();
  m_Player->left--;
}
