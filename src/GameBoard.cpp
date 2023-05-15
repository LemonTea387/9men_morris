#include "GameBoard.hpp"

#include <iostream>

#include "AssetManager.hpp"
#include "Observer/MillObserver.hpp"

GameBoard::GameBoard()
    : m_BoardShape(sf::Vector2f(BOARD_X, BOARD_Y)), m_State{PLACE} {
  AssetManager& assMan = AssetManager::GetInstance();
  m_BoardShape.setTexture(assMan.GetTexture(GameAsset::Texture::BOARD).get());
  m_BoardShape.setPosition(sf::Vector2f((Game::WINDOW_WIDTH - BOARD_X) / 2,
                                        (Game::WINDOW_HEIGHT - BOARD_Y) / 2));

  InitialiseTiles();

  m_Observers.push_back(new MillObserver(this));

  // Start the game at placing phase, all tiles are clickable
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      if (tile != nullptr) {
        tile->SetHighlight(true);
      }
  }
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
    if (m_P1Placed < 9 || m_P2Placed < 9) {
      // Continue Placing Phase
      m_State = PLACE;
      for (const auto& tile_rows : m_Board) {
        for (const auto& tile : tile_rows)
          if (tile != nullptr && !(tile->HasToken())) {
            tile->SetHighlight(true);
          }
      }
    } else{
        m_State = MOVE;
    }
    // Change Turn
    m_Turn = m_Turn == Token::Occupation::PEPE ? Token::Occupation::DOGE
                                               : Token::Occupation::PEPE;
  } else {
    // Capture Phase
    m_State = CAPTURE;
    // TODO:Highlight opponent tokens
  }
  m_ProgressTurn = false;
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
  command->execute();
  // TO-DO: Change to smart pointers, and store previously executed commands so
  // they can be undone

  // Cancel all highlights
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      if (tile != nullptr) {
        tile->SetHighlight(false);
      }
  }

  // Pass to observers
  for(const auto& observer: m_Observers) {
    observer->Notify(command->GetAffectedTile());
  }
  delete command;
  m_ProgressTurn = true;
}

void GameBoard::Placed(Token::Occupation occupation) {
  switch (occupation) {
    case Token::Occupation::PEPE:
      m_P1Placed++;
      break;
    case Token::Occupation::DOGE:
      m_P2Placed++;
      break;
  }
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

GameBoard::~GameBoard() {}

// void GameBoard::Notify(Tile* tile) {
//   curr_tile = tile;
//   if (curr_state == GameState::PLACE) {
//     place();
//   } else if (curr_state == GameState::MOVE) {
//     move();
//   } else if (curr_state == GameState::FLY) {
//     fly();
//   } else if (curr_state == GameState::CAPTURE) {
//     capture();
//   }
// }

// void GameBoard::move() {
//   if (tile_q.size() == 0) {
//     if (curr_tile->getOccupation() == turn) {
//       tile_q.push_back(curr_tile);
//     }
//   } else {
//     Tile* prev_tile = tile_q.at(0);
//     if (curr_tile->getOccupation() == turn) {
//       tile_q[0] = curr_tile;
//     } else if (curr_tile->getOccupation() == Tile::Occupation::NONE &&
//                curr_tile->isAdjacent(prev_tile)) {
//       tile_q.pop_back();
//       curr_tile->swapOccupation(prev_tile);
//       nextRound();
//     }
//   }
// }

// void GameBoard::fly() {
//   if (tile_q.size() == 0) {
//     if (curr_tile->getOccupation() == turn) {
//       tile_q.push_back(curr_tile);
//     }
//   } else {
//     Tile* prev_tile = tile_q.at(0);
//     if (curr_tile->getOccupation() == turn) {
//       tile_q[0] = curr_tile;
//     } else if (curr_tile->getOccupation() == Tile::Occupation::NONE) {
//       tile_q.pop_back();
//       curr_tile->swapOccupation(prev_tile);
//       nextRound();
//     }
//   }
// }

// void GameBoard::place() {
//   if (curr_tile->getOccupation() == Tile::Occupation::NONE) {
//     curr_tile->setOccupation(turn);
//     if (turn == Tile::Occupation::PEPE) {
//       p1_placed++;
//       p1_left++;
//     } else if (turn == Tile::Occupation::DOGE) {
//       p2_placed++;
//       p2_left++;
//     }
//     nextRound();
//   }
// }

// void GameBoard::capture() {
//   if (turn == Tile::Occupation::DOGE &&
//       curr_tile->getOccupation() == Tile::Occupation::PEPE) {
//     curr_tile->setOccupation(Tile::Occupation::NONE);
//     p2_left--;
//   } else if (turn == Tile::Occupation::PEPE &&
//              curr_tile->getOccupation() == Tile::Occupation::DOGE) {
//     curr_tile->setOccupation(Tile::Occupation::NONE);
//     p1_left--;
//   }

//   nextRound();
// }

// bool GameBoard::isWin() {
//   bool flag = false;
//   if (turn == Tile::Occupation::DOGE) {
//     flag = p1_placed == 9 && p1_left == 2;
//   } else if (turn == Tile::Occupation::PEPE) {
//     flag = p2_placed == 9 && p2_left == 2;
//   }
//   return flag;
// };

// bool GameBoard::isMill() {
//   bool flag = false;
//   int i = 0;
//   int horz_match = 0;
//   int vert_match = 0;

//   int horz_line = curr_tile->getHorzCoords().first;
//   int vert_line = curr_tile->getVertCoords().first;

//   for (i = 0; i < 3; i++) {
//     if (horz_board[horz_line][i]->getOccupation() == turn) {
//       horz_match++;
//     }
//     if (vert_board[vert_line][i]->getOccupation() == turn) {
//       vert_match++;
//     }
//   }

//   return horz_match == 3 || vert_match == 3;
// }

// void GameBoard::switch_turn() {
//   if (turn == Tile::Occupation::PEPE) {
//     turn = Tile::Occupation::DOGE;
//   } else if (turn == Tile::Occupation::DOGE) {
//     turn = Tile::Occupation::PEPE;
//   }
// }

// void GameBoard::nextRound() {
//   if (curr_state == GameState::CAPTURE && isWin()) {
//     // .......

//   } else if (isMill()) {
//     curr_state = GameState::CAPTURE;

//   } else {
//     if (turn == Tile::Occupation::PEPE) {
//       if (p2_placed < 9) {
//         curr_state = GameState::PLACE;
//       } else if (p2_left > 3) {
//         curr_state = GameState::MOVE;
//       } else if (p2_left == 3) {
//         curr_state = GameState::FLY;
//       }
//     } else if (turn == Tile::Occupation::DOGE) {
//       if (p1_placed < 9) {
//         curr_state = GameState::PLACE;
//       } else if (p1_left > 3) {
//         curr_state = GameState::MOVE;
//       } else if (p1_left == 3) {
//         curr_state = GameState::FLY;
//       }
//     }
//     switch_turn();
//   }
// }
