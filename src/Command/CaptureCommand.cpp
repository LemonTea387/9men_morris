#include "CaptureCommand.hpp"

#include "PlaceCommand.hpp"

CaptureCommand::CaptureCommand(TilePtr tile, Player* player)
    : Command::Command{tile, player} {}

CaptureCommand::~CaptureCommand() {}

void CaptureCommand::Execute() {
  // We want to Remove the current Tile's token, and modify the affected
  // player(captured player)'s attribute to signify that the affected player has
  // lost 1 token to capture.
  m_CapturedToken = m_AffectedTile->RemoveToken();
  m_Player->left--;
}

void CaptureCommand::Undo() {
  m_AffectedTile->SetToken(std::move(m_CapturedToken));
  m_CapturedToken = nullptr;
  m_Player->left++;
}

void CaptureCommand::AddToSaveGame(SaveGamePtr) {}
Command* CaptureCommand::RestoreFromSave(std::string save) {
  return new CaptureCommand(this->m_AffectedTile, this->m_Player);
}
