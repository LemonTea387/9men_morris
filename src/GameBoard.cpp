#include "GameBoard.hpp"

#include <iostream>
#include <string>

#include "AssetManager.hpp"
#include "GameBoardUtils.hpp"
#include "Observer/MillObserver.hpp"
#include "Observer/WinObserver.hpp"
#include "SFML/System/Vector2.hpp"

namespace {
/**
 * Constants for positioning the drawing of the remaining placement tokens of
 * DOGE.
 */
constexpr float DOGE_X_OFFSET = Game::WINDOW_WIDTH * 0.9f;
constexpr float DOGE_Y_OFFSET = Game::WINDOW_HEIGHT * 0.2f;

/**
 * Constants for positioning the drawing of the remaining placement tokens of
 * PEPE.
 */

constexpr float PEPE_X_OFFSET = Game::WINDOW_WIDTH * 0.05f;
constexpr float PEPE_Y_OFFSET = Game::WINDOW_HEIGHT * 0.2f;

/**
 * The spacings in between the drawing of remaining placement tokens for both
 * players.
 */
constexpr float TOKEN_LEFT_VERT_SPACING = 70.f;
}  // namespace

GameBoard::GameBoard()
    : m_BoardShape(sf::Vector2f(BOARD_X, BOARD_Y)),
      m_State{PLACE},
      m_P1{Token::Occupation::PEPE},
      m_P2{Token::Occupation::DOGE},
      m_Turn{&m_P1} {
  AssetManager& assMan = AssetManager::GetInstance();
  m_BoardShape.setTexture(assMan.GetTexture(GameAsset::Texture::BOARD).get());
  m_BoardShape.setPosition(sf::Vector2f((Game::WINDOW_WIDTH - BOARD_X) / 2,
                                        (Game::WINDOW_HEIGHT - BOARD_Y) / 2 - 50));

  InitialiseTiles();

  // Initialise the observers bound to GameBoard.
  m_Observers.push_back(std::make_unique<MillObserver>(this));
  // Win Observer has to be last, as it may require previous observing's
  // information
  m_Observers.push_back(std::make_unique<WinObserver>(this));

  // Start the game at placing phase
  HighlightValidMoves();

  // Tokens remaining to be placed for both players.
  m_DogeTokenLeft.setTexture(assMan.GetTexture(GameAsset::Texture::DOGE).get());
  m_PepeTokenLeft.setTexture(assMan.GetTexture(GameAsset::Texture::PEPE).get());
  m_DogeTokenLeft.setSize(sf::Vector2f(58.f, 60.f));
  m_PepeTokenLeft.setSize(sf::Vector2f(58.f, 60.f));

  // Compile the Shaders

  // Shader Code for drawing TokensLeft
  // Yes, it is normal to have the source code here loaded through a file. It is
  // sent to the GPU to be compiled.
  //
  // In the case they can't be compiled, the fallback is that the display
  // is still drawn, but with no special effects.

  // Learnt through
  // https://www.sfml-dev.org/tutorials/2.5/graphics-shader.php
  // and https://learnopengl.com/Getting-started/Shaders
  if (!m_TokenLeftShader.loadFromFile("assets/shaders/TokensLeft.vert",
                                      sf::Shader::Vertex)) {
    std::cerr << "[WARNING] Could not load Vertex Shader for TokenLeft display!"
              << std::endl;
  }
  if (!m_TokenLeftShader.loadFromFile("assets/shaders/TokensLeft.frag",
                                      sf::Shader::Fragment)) {
    std::cerr
        << "[WARNING] Could not load Fragment Shader for TokenLeft display!"
        << std::endl;
  }
}

GameBoard::~GameBoard() {}

void GameBoard::Update(sf::Event event) {
  // Notifying the underlying listeners (Tiles) to see if there's an update.
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
    // We have progressed this turn, turn off the flag.
    m_ProgressTurn = false;

    // Highlight the current turn's valid moves.
    HighlightValidMoves();
  }
}

void GameBoard::Render(sf::RenderWindow& window) {
  // Draw the board.
  window.draw(m_BoardShape);
  // Drawing of all the tiles.
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      if (tile != nullptr) {
        window.draw(*tile);
      }
  }

  // Draw the "Tokens Left to be placed" display

  m_TokenLeftShader.setUniform("texture", sf::Shader::CurrentTexture);
  m_TokenLeftShader.setUniform("transparency", 0.5f);

  constexpr int TOKENS_PER_GAME = 9;

  // Draw Tokens left display for Doge
  for (int curToken = 0; curToken < TOKENS_PER_GAME - m_P2.placed; curToken++) {
    m_DogeTokenLeft.setPosition(sf::Vector2f(
        DOGE_X_OFFSET, DOGE_Y_OFFSET + (curToken * TOKEN_LEFT_VERT_SPACING)));
    window.draw(m_DogeTokenLeft, &m_TokenLeftShader);
  }

  // Draw Tokens left display for Pepe
  for (int curToken = 0; curToken < TOKENS_PER_GAME - m_P1.placed; curToken++) {
    m_PepeTokenLeft.setPosition(sf::Vector2f(
        PEPE_X_OFFSET, PEPE_Y_OFFSET + (curToken * TOKEN_LEFT_VERT_SPACING)));
    window.draw(m_PepeTokenLeft, &m_TokenLeftShader);
  }
}

void GameBoard::ExecuteCommand(Command* command) {
  command->Execute();
  // Pass to observers
  for (const auto& observer : m_Observers) {
    observer->Notify(command->GetAffectedTile());
  }

  // TODO : Store the Commands in a Stack to be undo'd
  delete command;

  // Remove the active selected tile.
  m_ActiveTile = nullptr;
  // Executed a command, progress to next turn.
  m_ProgressTurn = true;
}

void GameBoard::SetActiveTile(Tile* tile) {
  m_ActiveTile = tile;
  // For this activated tile, highlight its valid moves.
  HighlightValidMoves();
};

std::vector<Tile*> GameBoard::CalculateValidMoves(GameState state, Player* turn,
                                                  Tile* activeTile) {
  // All the tiles available for easy traversal later.
  std::vector<Tile*> tiles{};
  // The return vector for all the valid tiles' pointer.
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
  } else if (state == GameBoard::MOVE && activeTile != nullptr) {
    // Display possible moves from that active tile
    // Case 1 : > 3 pieces left, Highlight adjacent empty tiles
    if (turn->left > 3) {
      for (const auto& tileCoord :
           Util::GetNeighbours(activeTile->GetTileCoord())) {
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
          tile->GetToken()->GetOccupation() != turn->occupation &&
          !Util::isMill(this, tile)) {
        validTiles.push_back(tile);
        validCount++;
      }
    if (validCount == 0) {
      // No other tiles not in mill, every opponent's tokens' is valid
      for (const auto& tile : tiles)
        if (tile->HasToken() &&
            tile->GetToken()->GetOccupation() != turn->occupation) {
          validTiles.push_back(tile);
        }
    }
  }

  return validTiles;
}

void GameBoard::InitialiseTiles() {
  // These are the coordinates where there can be a tile, may want to move it
  // somewhere else for not having to change this function if any change.
  constexpr int coordinates[24][2]{
      {0, 0}, {3, 0}, {6, 0}, {1, 1}, {3, 1}, {5, 1}, {2, 2}, {3, 2},
      {4, 2}, {0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 3}, {6, 3}, {2, 4},
      {3, 4}, {4, 4}, {1, 5}, {3, 5}, {5, 5}, {0, 6}, {3, 6}, {6, 6}};
  for (const auto& coord : coordinates) {
    m_Board[coord[0]][coord[1]] =
        std::make_unique<Tile>(this, TileCoord{coord[0], coord[1]});
    // The position is determined by the coordinates.
    m_Board[coord[0]][coord[1]]->setPosition(
        {TILE_X_PAD + coord[0] * TILE_DIM - TILE_DIM / 3,
         TILE_Y_PAD + coord[1] * TILE_DIM - TILE_DIM / 3});
  }
}

void GameBoard::HighlightValidMoves() {
  // Remove previous highlighting first
  CancelHighlight();
  // Highlight the valid moves for the current state, turn and activetile.
  for (const auto& tile : CalculateValidMoves(m_State, m_Turn, m_ActiveTile)) {
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
  // The return tiles vector.
  std::vector<Tile*> tiles{};
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      // If tile has a token and the token is matching the player's occupation.
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
  // Check against the current player if it's the same then it's the other
  // player
  return &m_P1 == m_Turn ? &m_P2 : &m_P1;
}

bool GameBoard::GetHasMillCapture() const { return m_HasMillCapture; }

GameBoard::GameState GameBoard::GetState() const { return m_State; }
