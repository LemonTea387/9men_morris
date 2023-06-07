#include "PlaceCommand.hpp"

#include <memory>
#include <sstream>

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
  out << m_AffectedTile->serialize();
  out << m_Player->left << m_Player->placed << m_Player->occupation;
  sg->AddToSave(out.str(), this);
}
void PlaceCommand::RestoreFromSave(std::string save) {}
