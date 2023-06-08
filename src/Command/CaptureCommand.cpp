#include "CaptureCommand.hpp"

#include <iostream>
#include <sstream>

#include "../GameBoard.hpp"
#include "../SaveGame.hpp"

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
  // Restore the captured token to original tile
  m_AffectedTile->SetToken(std::move(m_CapturedToken));
  m_CapturedToken = nullptr;
  m_Player->left++;
}

void CaptureCommand::AddToSaveGame(SaveGamePtr sg) {
  // CAPTURE [tile] [player-left] [player-placed] [player-occupation]
  std::stringstream out;
  out << "CAPTURE ";
  out << m_AffectedTile->serialize();
  out << m_Player->left << " " << m_Player->placed << " "
      << m_Player->occupation;

  // Add this command to memento
  sg->AddToSave(out.str());
}
void CaptureCommand::RestoreFromSave(std::string save, GameBoard* gb) {
  std::stringstream instream(save);
  std::string magic;
  instream >> magic;
  const auto magic_assert = [&](std::string comparison) {
    if (magic != comparison) {
      std::cerr << "Savegame Invalid command " << magic << " when expected "
                << comparison << "!" << std::endl;
      return;
    }
  };
  magic_assert("CAPTURE");
  instream >> magic;
  magic_assert("TILE");

  // Parsing 
  int xCoord, yCoord;
  instream >> xCoord;
  instream >> yCoord;

  Tile* tile = gb->GetTile(xCoord, yCoord);

  // This is not used
  bool highlighted;
  instream >> highlighted;

  m_AffectedTile = tile;

  // Parses the remaining player data
  int left, placed;
  int occupation;
  instream >> left;
  instream >> placed;
  instream >> occupation;
  // Safe cast since enums are just ints under the hood anyway.
  m_Player = gb->GetPlayer(static_cast<Token::Occupation>(occupation));
}
