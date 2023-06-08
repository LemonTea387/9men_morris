#include "MoveCommand.hpp"

#include <iostream>
#include <sstream>

#include "../GameBoard.hpp"
#include "../SaveGame.hpp"

MoveCommand::MoveCommand(TilePtr srcTile, TilePtr dstTile, Player* player)
    : Command::Command(dstTile, player), m_SrcTile{srcTile} {}

MoveCommand::~MoveCommand() {}

void MoveCommand::Execute() {
  // Check to see if source Tile is valid and it has tokens.
  if (!m_SrcTile || !(m_SrcTile->HasToken())) return;
  m_SrcTile->MoveToken(m_AffectedTile);
}

void MoveCommand::Undo() { m_AffectedTile->MoveToken(m_SrcTile); }
void MoveCommand::AddToSaveGame(SaveGamePtr sg) {
  // MOVE [src_tile] [dest_tile] [player-left] [player-placed]
  // [player-occupation]
  std::stringstream out;
  out << "MOVE ";
  out << m_SrcTile->serialize();
  out << m_AffectedTile->serialize();
  out << m_Player->left << " " << m_Player->placed << " "
      << m_Player->occupation;
  sg->AddToSave(out.str());
}
void MoveCommand::RestoreFromSave(std::string save, GameBoard* gb) {
  std::stringstream instream(save);
  std::string magic;
  const auto magic_assert = [&](std::string comparison) {
    if (magic != comparison) {
      std::cerr << "Savegame Invalid command " << magic << " when expected "
                << comparison << "!" << std::endl;
      return;
    }
  };
  instream >> magic;
  magic_assert("MOVE");
  instream >> magic;

  // Retrieve src tile
  magic_assert("TILE");
  int xCoord, yCoord;
  bool highlighted;
  instream >> xCoord;
  instream >> yCoord;
  instream >> highlighted;

  Tile* tile = gb->GetTile(xCoord, yCoord);
  m_SrcTile = tile;

  // Retrieve dest tile
  instream >> magic;
  magic_assert("TILE");
  instream >> xCoord;
  instream >> yCoord;
  instream >> highlighted;

  tile = gb->GetTile(xCoord, yCoord);
  m_AffectedTile = tile;

  // retrieve player
  int left, placed;
  int occupation;
  instream >> left;
  instream >> placed;
  instream >> occupation;
  // Safe cast since enums are just ints under the hood anyway.
  m_Player = gb->GetPlayer(static_cast<Token::Occupation>(occupation));
}
