#include "GameBoard.hpp"

#include <iostream>
#include "AssetManager.hpp"

void GameBoard::Update(sf::Event event) {}

void GameBoard::Render(sf::RenderWindow& window) {
  window.draw(m_BoardShape);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      window.draw(*horz_board[i][j]);
    }
  }
}

GameBoard::GameBoard() : m_BoardShape(sf::Vector2f(554.f, 554.f)) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      horz_board[i][j] = std::make_unique<Tile>(this);
    }
  }

  m_BoardShape.setPosition(sf::Vector2f(223.f, 173.f));
  AssetManager& assMan = AssetManager::GetInstance();
  if (!m_BoardTexture.loadFromFile("assets/ui/gameBoard.png")) {
    std::cerr << "Could not load Board Texture!" << std::endl;
  }
  m_BoardShape.setTexture(&m_BoardTexture);

  InitialiseTiles();

  p1_left = 0;
  p2_left = 0;
  p1_placed = 0;
  p2_placed = 0;

  turn = Tile::Occupation::PEPE;
  curr_state = GameState::PLACE;
}

void GameBoard::InitialiseTiles() {
  int tile_pos[24][2] = {
      {197, 141}, {467, 141}, {732, 141}, {287, 234}, {467, 234}, {642, 234},
      {374, 324}, {467, 324}, {552, 324}, {197, 411}, {287, 411}, {374, 411},
      {554, 411}, {642, 411}, {732, 411}, {374, 497}, {467, 497}, {554, 497},
      {287, 589}, {467, 589}, {642, 589}, {197, 677}, {467, 677}, {732, 677},
  };

  int coordinates[24][2][2] = {
      {{0, 0}, {0, 0}}, {{0, 1}, {3, 0}}, {{0, 2}, {7, 0}}, 
      {{1, 0}, {1, 0}}, {{1, 1}, {3, 1}}, {{1, 2}, {6, 0}}, 
      {{2, 0}, {2, 0}}, {{2, 1}, {3, 2}}, {{2, 2}, {5, 0}}, 
      {{3, 0}, {0, 1}}, {{3, 1}, {1, 1}}, {{3, 2}, {2, 1}},
      {{4, 0}, {5, 1}}, {{4, 1}, {6, 1}}, {{4, 2}, {7, 1}}, 
      {{5, 0}, {2, 2}}, {{5, 1}, {4, 0}}, {{5, 2}, {5, 2}}, 
      {{6, 0}, {1, 2}}, {{6, 1}, {4, 1}}, {{6, 2}, {6, 2}}, 
      {{7, 0}, {0, 2}}, {{7, 1}, {4, 2}}, {{7, 2}, {7, 2}}};

  int k;
  Tile* new_tile;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      k = i * 3 + j;
      new_tile = horz_board[i][j].get();
      new_tile->setHorzCoords(coordinates[k][0][0], coordinates[k][0][1]);
      new_tile->setVertCoords(coordinates[k][1][0], coordinates[k][1][1]);
      new_tile->setPosition(sf::Vector2f(tile_pos[k][0], tile_pos[k][1]));
      new_tile->setSize(sf::Vector2f(72, 78));
      new_tile->setOccupation(Tile::Occupation::NONE);
      vert_board[coordinates[k][1][0]][coordinates[k][1][1]] = new_tile ;
    }
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
    } else if (curr_tile->getOccupation() ==
               Tile::Occupation::NONE && curr_tile->isAdjacent(prev_tile)) {
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
