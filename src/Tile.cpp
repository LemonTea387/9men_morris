#include "Tile.hpp"

#include <iostream>

#include "AssetManager.hpp"
#include "Command/CaptureCommand.hpp"
#include "Command/MoveCommand.hpp"
#include "Command/PlaceCommand.hpp"
#include "GameBoard.hpp"

Tile::Tile(GameBoard* gb, TileCoord coord)
    : m_Gameboard{gb}, graphics::Button(""), m_Coord{coord} {
  // Textures
  AssetManager& assMan = AssetManager::GetInstance();
  m_DefaultTexture = assMan.GetTexture(GameAsset::Texture::TILE).get();
  m_HighlightTexture =
      assMan.GetTexture(GameAsset::Texture::HIGHLIGHT_TILE).get();
  setTexture(m_DefaultTexture);

  this->setCallback([&](sf::Event event) {
    // Perform command
    if (m_Highlight) {
      switch (m_Gameboard->GetState()) {
        case GameBoard::PLACE:
          m_Gameboard->ExecuteCommand(
              new PlaceCommand{this, m_Gameboard->GetCurrPlayer()});
          break;
        case GameBoard::CAPTURE:
          m_Gameboard->ExecuteCommand(
              new CaptureCommand{this, m_Gameboard->GetOpponentPlayer()});
          break;
        case GameBoard::MOVE:
          m_Gameboard->ExecuteCommand(
              new MoveCommand{m_Gameboard->GetActiveTile(), this,
                              m_Gameboard->GetCurrPlayer()});
          break;
      }
    }
    // Activate the tile in gameboard
    else if (HasToken() && GetToken()->GetOccupation() ==
                               m_Gameboard->GetCurrPlayer()->occupation) {
      m_Gameboard->SetActiveTile(this);
    }
  });
};

Tile::~Tile(){};

Token* Tile::GetToken() const { return m_Token.get(); };

bool Tile::HasToken() const { return m_Token != nullptr; };

void Tile::RemoveToken() { m_Token = nullptr; };

void Tile::SetHighlight(bool highlight) {
  if (m_Highlight == highlight) return;

  m_Highlight = highlight;
  if (HasToken()) {
    if (highlight)
      GetToken()->SetState(Token::TokenState::SCREAM);
    else
      GetToken()->SetState(Token::TokenState::NORMAL);
  } else {
    if (highlight)
      setTexture(m_HighlightTexture);
    else
      setTexture(m_DefaultTexture);
  }
}

void Tile::SetToken(std::unique_ptr<Token> token) {
  // Dirty fix for cancelling prior empty tile highlight textures when setting a
  // token.
  setTexture(m_DefaultTexture);
  m_Token = std::move(token);
};

void Tile::MoveToken(Tile* dstTile) {
  m_Token->SetPosition(dstTile->getPosition());
  dstTile->SetToken(std::move(m_Token));
  m_Token = nullptr;
};

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  Button::draw(target, states);
  if (m_Token != nullptr) {
    target.draw(*m_Token);
  }
}

TileCoord Tile::GetTileCoord() const { return m_Coord; };
