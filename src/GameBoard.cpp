#include "GameBoard.hpp"

#include <iostream>

#include "AssetManager.hpp"
#include "Observer/MillObserver.hpp"

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

  // Start the game at placing phase
  CalculateValidMoves();
}

void GameBoard::Update(sf::Event event) {
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      if (tile != nullptr) {
        tile->notifyListeners(event);
      }
  }
  // No command executed
  if (!m_ProgressTurn) return;

  // Handle turns
  if (!m_HasMill) {
    if (m_P1.placed < 9 || m_P2.placed < 9) {
      // Continue Placing Phase
      m_State = PLACE;
    } else {
      m_State = MOVE;
    }
    // Change Turn
    m_Turn = m_Turn == &m_P1 ? &m_P2 : &m_P1;
  } else {
    // Capture Phase
    m_State = CAPTURE;
  }
  m_ProgressTurn = false;

  CalculateValidMoves();
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
  // TO-DO: Change to smart pointers, and store previously executed commands so
  // they can be undone

  // Cancel all highlights
  CancelHighlight();

  // Pass to observers
  for (const auto& observer : m_Observers) {
    observer->Notify(command->GetAffectedTile());
  }

  delete command;
  m_ActiveTile = nullptr;
  m_ProgressTurn = true;
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

void GameBoard::CalculateValidMoves() {
  // Remove previous highlighting first
  CancelHighlight();

  // Highlighting based on gamestates
  if (m_State == GameBoard::PLACE) {
    // All empty tiles should be placeable
    for (const auto& tile_rows : m_Board) {
      for (const auto& tile : tile_rows)
        if (tile != nullptr && !(tile->HasToken())) {
          tile->SetHighlight(true);
        }
    }
  } else if (m_State == GameBoard::MOVE && m_ActiveTile != nullptr) {
    // Display possible moves from that active tile
    // Case 1 : > 3 pieces left, Highlight adjacent empty tiles
    if (m_Turn->left > 3) {
      
      return;
    }
    // Case 2 : 3 pieces left, fly (highlight all empty tiles)
    for (const auto& tile_rows : m_Board) {
      for (const auto& tile : tile_rows)
        if (tile != nullptr && !(tile->HasToken())) {
          tile->SetHighlight(true);
        }
    }
  } else if (m_State == GameBoard::CAPTURE) {
    // Highlight all capturable tiles
  }
}

GameBoard::~GameBoard() {}
