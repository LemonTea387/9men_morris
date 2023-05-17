#include "GameBoard.hpp"

#include "AssetManager.hpp"
#include "GameBoardUtils.hpp"
#include "Observer/MillObserver.hpp"
#include "Observer/WinObserver.hpp"

GameBoard::GameBoard()
    : m_BoardShape(sf::Vector2f(BOARD_X, BOARD_Y)),
      m_State{PLACE},
      m_P1{Token::Occupation::PEPE},
      m_P2{Token::Occupation::DOGE},
      m_Turn{&m_P1} {
  AssetManager& assMan = AssetManager::GetInstance();
  m_BoardShape.setTexture(assMan.GetTexture(GameAsset::Texture::BOARD).get());
  m_BoardShape.setPosition(sf::Vector2f((Game::WINDOW_WIDTH - BOARD_X) / 2,
                                        (Game::WINDOW_HEIGHT - BOARD_Y) / 2));

  InitialiseTiles();

  m_Observers.push_back(new MillObserver(this));
  // Win Observer has to be last, as it may require previous observing's
  // information
  m_Observers.push_back(new WinObserver(this));

  // Start the game at placing phase
  HighlightValidMoves();
}

GameBoard::~GameBoard() {}

void GameBoard::Update(sf::Event event) {
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      if (tile != nullptr) {
        tile->notifyListeners(event);
      }
  }
  // No command executed
  if (m_ProgressTurn) {
    // Handle turns
    if (!m_HasMillCapture) {
      // Either Place or Move based on if it's done placing or not
      m_State = (m_P1.placed < 9 || m_P2.placed < 9) ? PLACE : MOVE;
      // Change Turn
      m_Turn = m_Turn == &m_P1 ? &m_P2 : &m_P1;
    } else {
      // Capture Phase
      m_State = CAPTURE;
      m_HasMillCapture = false;
    }
    m_ProgressTurn = false;

    HighlightValidMoves();
  }
}

void GameBoard::Render(sf::RenderWindow& window) {
  window.draw(m_BoardShape);
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      if (tile != nullptr) {
        window.draw(*tile);
      }
  }
}

void GameBoard::ExecuteCommand(Command* command) {
  command->Execute();
  // Pass to observers
  for (const auto& observer : m_Observers) {
    observer->Notify(command->GetAffectedTile());
  }

  delete command;
  m_ActiveTile = nullptr;
  m_ProgressTurn = true;
}

void GameBoard::SetActiveTile(Tile* tile) {
  m_ActiveTile = tile;
  HighlightValidMoves();
};

std::vector<Tile*> GameBoard::CalculateValidMoves(GameState state,
                                                  Tile* activeTile) {
  std::vector<Tile*> tiles{};
  std::vector<Tile*> validTiles{};

  // Get the tiles first
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows) {
      if (tile != nullptr) tiles.push_back(tile.get());
    }
  }

  // Highlighting based on gamestates
  if (state == GameBoard::PLACE) {
    // All empty tiles should be placeable
    for (const auto& tile : tiles)
      if (!(tile->HasToken())) {
        validTiles.push_back(tile);
      }
  } else if (state == GameBoard::MOVE && m_ActiveTile != nullptr) {
    // Display possible moves from that active tile
    // Case 1 : > 3 pieces left, Highlight adjacent empty tiles
    if (m_Turn->left > 3) {
      for (const auto& tileCoord :
           Util::GetNeighbours(m_ActiveTile->GetTileCoord())) {
        auto tile{GetTile(tileCoord.first, tileCoord.second)};
        if (!tile->HasToken()) {
          validTiles.push_back(tile);
        }
      }
    } else {
      // Case 2 : 3 pieces left, fly (All empty tiles are valid)
      for (const auto& tile : tiles)
        if (tile != nullptr && !(tile->HasToken())) {
          validTiles.push_back(tile);
        }
    }
  } else if (state == GameBoard::CAPTURE) {
    // Highlight all capturable tiles
    // If it's in a mill, not valid unless no other tiles not in mill
    int validCount = 0;
    for (const auto& tile : tiles)
      if (tile->HasToken() &&
          tile->GetToken()->GetOccupation() != m_Turn->occupation &&
          !Util::isMill(this, tile)) {
        validTiles.push_back(tile);
        validCount++;
      }
    if (validCount == 0) {
      // No other tiles not in mill, every opponent's tokens' is valid
      for (const auto& tile : tiles)
        if (tile->HasToken() &&
            tile->GetToken()->GetOccupation() != m_Turn->occupation) {
          validTiles.push_back(tile);
        }
    }
  }

  return validTiles;
}

void GameBoard::InitialiseTiles() {
  constexpr int coordinates[24][2]{
      {0, 0}, {3, 0}, {6, 0}, {1, 1}, {3, 1}, {5, 1}, {2, 2}, {3, 2},
      {4, 2}, {0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 3}, {6, 3}, {2, 4},
      {3, 4}, {4, 4}, {1, 5}, {3, 5}, {5, 5}, {0, 6}, {3, 6}, {6, 6}};
  for (const auto& coord : coordinates) {
    m_Board[coord[0]][coord[1]] =
        std::make_unique<Tile>(this, TileCoord{coord[0], coord[1]});
    m_Board[coord[0]][coord[1]]->setPosition(
        {TILE_X_PAD + coord[0] * TILE_DIM - TILE_DIM / 3,
         TILE_Y_PAD + coord[1] * TILE_DIM - TILE_DIM / 3});
  }
}

void GameBoard::HighlightValidMoves() {
  // Remove previous highlighting first
  CancelHighlight();
  for (const auto& tile : CalculateValidMoves(m_State, m_ActiveTile)) {
    tile->SetHighlight(true);
  }
}

void GameBoard::CancelHighlight() {
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      if (tile != nullptr) {
        tile->SetHighlight(false);
      }
  }
}

std::vector<Tile*> GameBoard::GetPlayerTiles(Player* player) {
  std::vector<Tile*> tiles{};
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      if (tile != nullptr && tile->HasToken() &&
          tile->GetToken()->GetOccupation() == player->occupation) {
        tiles.push_back(tile.get());
      }
  }
  return tiles;
}

void GameBoard::SetMillFlag(bool flag) { m_HasMillCapture = flag; }

Tile* GameBoard::GetActiveTile() { return m_ActiveTile; }

Tile* GameBoard::GetTile(int x, int y) const { return m_Board[x][y].get(); }

Player* GameBoard::GetCurrPlayer() { return m_Turn; }

Player* GameBoard::GetOpponentPlayer() {
  return &m_P1 == m_Turn ? &m_P2 : &m_P1;
}

bool GameBoard::GetMillCapture() const { return m_HasMillCapture; }

GameBoard::GameState GameBoard::GetState() const { return m_State; }
