#include "PlaceCommand.hpp"

#include <memory>

#include "../Token.hpp"

void PlaceCommand::execute() {
  m_AffectedTile->SetToken(std::move(
      std::make_unique<Token>(m_Occupation, m_AffectedTile->getPosition())));
}

PlaceCommand::PlaceCommand(TilePtr tile, Token::Occupation occupation)
    : Command::Command(tile), m_Occupation{occupation} {

    }

PlaceCommand::~PlaceCommand() {}
