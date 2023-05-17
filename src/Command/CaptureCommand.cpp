#include "CaptureCommand.hpp"

CaptureCommand::CaptureCommand(TilePtr tile, Player* player)
    : Command::Command{tile, player} {}

CaptureCommand::~CaptureCommand() {}

void CaptureCommand::Execute() {
  // We want to Remove the current Tile's token, and modify the affected
  // player(captured player)'s attribute to signify that the affected player has
  // lost 1 token to capture.
  m_AffectedTile->RemoveToken();
  m_Player->left--;
}
