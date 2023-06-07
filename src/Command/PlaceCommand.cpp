#include "PlaceCommand.hpp"

#include <iostream>
#include <memory>
#include <sstream>

#include "../GameBoard.hpp"
#include "../SaveGame.hpp"
#include "../Token.hpp"

PlaceCommand::PlaceCommand(TilePtr tile, Player* player)
    : Command::Command(tile, player) {}

PlaceCommand::~PlaceCommand() {}

void PlaceCommand::Execute() {
  // Make a new token and set it to the Tile
  // The move usage here is to transfer the ownership to the Tile from the
  // PlaceCommand.
  m_AffectedTile->SetToken(std::move(std::make_unique<Token>(
      m_Player->occupation, m_AffectedTile->getPosition())));
  // Count that the player has placed a new token
  m_Player->placed++;
}

void PlaceCommand::Undo() {
  m_AffectedTile->RemoveToken();
  m_Player->placed--;
}
void PlaceCommand::AddToSaveGame(SaveGamePtr sg) {
  std::stringstream out;
  out << "PLACE ";
  out << m_AffectedTile->serialize();
  out << m_Player->left << " " << m_Player->placed << " "
      << m_Player->occupation;
  sg->AddToSave(out.str());
}
void PlaceCommand::RestoreFromSave(std::string save, GameBoard* gb) {
  std::stringstream instream(save);
  std::string magic;
  instream >> magic;
  const auto magic_assert = [&](std::string comparison) {
    if (magic != comparison) {
      std::cerr << "Savegame Invalid command " << magic << "!" << std::endl;
      return;
    }
  };
  magic_assert("PLACE");
  instream >> magic;
  magic_assert("TILE");

  int xCoord, yCoord;
  instream >> xCoord;
  instream >> yCoord;

  Tile* tile = gb->GetTile(xCoord, yCoord);

  bool highlighted;
  instream >> highlighted;

  m_AffectedTile = tile;

  int left, placed;
  int occupation;
  instream >> left;
  instream >> placed;
  instream >> occupation;
  // Safe cast since enums are just ints under the hood anyway.
  m_Player = gb->GetPlayer(static_cast<Token::Occupation>(occupation));
}
