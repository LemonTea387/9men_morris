#include "GameBoard.hpp"

#include <iostream>

#include "AssetManager.hpp"

void GameBoard::Update(sf::Event event) {}

void GameBoard::Render(sf::RenderWindow& window) {
  window.draw(m_BoardShape);
  for (const auto& tile_rows : m_Board) {
    for (const auto& tile : tile_rows)
      if (tile != nullptr) {
        window.draw(*tile);
      }
  }
}

GameBoard::GameBoard() : m_BoardShape(sf::Vector2f(554.f, 554.f)) {
  m_BoardShape.setPosition(sf::Vector2f(223.f, 173.f));
  AssetManager& assMan = AssetManager::GetInstance();
  m_BoardShape.setTexture(assMan.GetTexture(GameAsset::Texture::BOARD).get());

  InitialiseTiles();

  p1_left = 0;
  p2_left = 0;
  p1_placed = 0;
  p2_placed = 0;

  turn = Tile::Occupation::PEPE;
  curr_state = GameState::PLACE;
}

void GameBoard::InitialiseTiles() {
  const float x_pad = 197.;
  const float y_pad = 141.;
  constexpr int coordinates[24][2]{
      {0, 0}, {3, 0}, {6, 0}, {1, 1}, {3, 1}, {5, 1}, {2, 2}, {3, 2},
      {4, 2}, {0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 3}, {6, 3}, {2, 4},
      {3, 4}, {4, 4}, {1, 5}, {3, 5}, {5, 5}, {0, 6}, {3, 6}, {6, 6}};
  for (const auto& coord : coordinates) {
    m_Board[coord[0]][coord[1]] = std::make_unique<Tile>(this);
    m_Board[coord[0]][coord[1]]->setPosition(
        {x_pad + coord[0] * 90, y_pad + coord[1] * 90});

    // TODO : CHANGE THIS
    m_Board[coord[0]][coord[1]]->setOccupation(Tile::Occupation::NONE);
  }
}

GameBoard::~GameBoard() {}

void GameBoard::Notify(Tile* tile) {
  curr_tile = tile;
  if (curr_state == GameState::PLACE) {
    place();
  } else if (curr_state == GameState::MOVE) {
    move();
  } else if (curr_state == GameState::FLY) {
    fly();
  } else if (curr_state == GameState::CAPTURE) {
    capture();
  }
}

void GameBoard::move() {
  if (tile_q.size() == 0) {
    if (curr_tile->getOccupation() == turn) {
      tile_q.push_back(curr_tile);
    }
  } else {
    Tile* prev_tile = tile_q.at(0);
    if (curr_tile->getOccupation() == turn) {
      tile_q[0] = curr_tile;
    } else if (curr_tile->getOccupation() == Tile::Occupation::NONE &&
               curr_tile->isAdjacent(prev_tile)) {
      tile_q.pop_back();
      curr_tile->swapOccupation(prev_tile);
      nextRound();
    }
  }
}

void GameBoard::fly() {
  if (tile_q.size() == 0) {
    if (curr_tile->getOccupation() == turn) {
      tile_q.push_back(curr_tile);
    }
  } else {
    Tile* prev_tile = tile_q.at(0);
    if (curr_tile->getOccupation() == turn) {
      tile_q[0] = curr_tile;
    } else if (curr_tile->getOccupation() == Tile::Occupation::NONE) {
      tile_q.pop_back();
      curr_tile->swapOccupation(prev_tile);
      nextRound();
    }
  }
}

void GameBoard::place() {
  if (curr_tile->getOccupation() == Tile::Occupation::NONE) {
    curr_tile->setOccupation(turn);
    if (turn == Tile::Occupation::PEPE) {
      p1_placed++;
      p1_left++;
    } else if (turn == Tile::Occupation::DOGE) {
      p2_placed++;
      p2_left++;
    }
    nextRound();
  }
}

void GameBoard::capture() {
  if (turn == Tile::Occupation::DOGE &&
      curr_tile->getOccupation() == Tile::Occupation::PEPE) {
    curr_tile->setOccupation(Tile::Occupation::NONE);
    p2_left--;
  } else if (turn == Tile::Occupation::PEPE &&
             curr_tile->getOccupation() == Tile::Occupation::DOGE) {
    curr_tile->setOccupation(Tile::Occupation::NONE);
    p1_left--;
  }

  nextRound();
}

bool GameBoard::isWin() {
  bool flag = false;
  if (turn == Tile::Occupation::DOGE) {
    flag = p1_placed == 9 && p1_left == 2;
  } else if (turn == Tile::Occupation::PEPE) {
    flag = p2_placed == 9 && p2_left == 2;
  }
  return flag;
};

bool GameBoard::isMill() {
  bool flag = false;
  int i = 0;
  int horz_match = 0;
  int vert_match = 0;

  int horz_line = curr_tile->getHorzCoords().first;
  int vert_line = curr_tile->getVertCoords().first;

  for (i = 0; i < 3; i++) {
    if (horz_board[horz_line][i]->getOccupation() == turn) {
      horz_match++;
    }
    if (vert_board[vert_line][i]->getOccupation() == turn) {
      vert_match++;
    }
  }

  return horz_match == 3 || vert_match == 3;
}

void GameBoard::switch_turn() {
  if (turn == Tile::Occupation::PEPE) {
    turn = Tile::Occupation::DOGE;
  } else if (turn == Tile::Occupation::DOGE) {
    turn = Tile::Occupation::PEPE;
  }
}

void GameBoard::nextRound() {
  if (curr_state == GameState::CAPTURE && isWin()) {
    // .......

  } else if (isMill()) {
    curr_state = GameState::CAPTURE;

  } else {
    if (turn == Tile::Occupation::PEPE) {
      if (p2_placed < 9) {
        curr_state = GameState::PLACE;
      } else if (p2_left > 3) {
        curr_state = GameState::MOVE;
      } else if (p2_left == 3) {
        curr_state = GameState::FLY;
      }
    } else if (turn == Tile::Occupation::DOGE) {
      if (p1_placed < 9) {
        curr_state = GameState::PLACE;
      } else if (p1_left > 3) {
        curr_state = GameState::MOVE;
      } else if (p1_left == 3) {
        curr_state = GameState::FLY;
      }
    }
    switch_turn();
  }
}
