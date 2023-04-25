#include "GameBoard.hpp"

#include <iostream>

#include "Game.hpp"
#include "Tile.hpp"
#include "AssetManager.hpp"

void GameBoard::Update(sf::Event event) {
}

void GameBoard::Render() {
  sf::RenderWindow &window = Game::GetWindow();
  window.draw(m_Board);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      window.draw(*horizontal_board[i][j]);
    }
  }
}

GameBoard::GameBoard() : m_Board(sf::Vector2f(554.f, 554.f)) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      horizontal_board[i][j] = std::make_unique<Tile::Tile>(this);
    }
  }

  m_Board.setPosition(sf::Vector2f(223.f, 173.f));
  AssetManager& assMan = AssetManager::GetInstance();
  if (!m_BoardTexture.loadFromFile("assets/ui/gameBoard.png")) {
    std::cerr << "Could not load Board Texture!" << std::endl;
  }
  m_Board.setTexture(&m_BoardTexture);

  InitialiseTiles();
  Render();
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

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      k = i * 3 + j;
      new_tile = horizontal_board[i][j].get();
      new_tile->setHorzCoords(coordinates[k][0][0], coordinates[k][0][1]);
      new_tile->setVertCoords(coordinates[k][1][0], coordinates[k][1][1]);
      new_tile->setPosition(sf::Vector2f(tile_pos[k][0], tile_pos[k][1]));
      new_tile->setSize(sf::Vector2f(72, 78));
      new_tile->setOccupation(Tile::Occupation::NONE);

      if (k < 9) {
        new_tile->setOccupation(Tile::Occupation::DOGE);
      } else if (k >= 15) {
        new_tile->setOccupation(Tile::Occupation::PEPE);
      } 
    }
  }
}

GameBoard::~GameBoard() {}

void GameBoard::Notify(Tile::Tile* curr_tile) {
  if (tile_q.size() == 0) {
    if (curr_tile->getOccupation() != Tile::Occupation::NONE) {
      tile_q.push_back(curr_tile);
    }
  } else {
    Tile::Tile *prev_tile = tile_q.at(0);
    if (curr_tile->getOccupation() != Tile::Occupation::NONE) {
      tile_q.pop_back();
      tile_q.push_back(curr_tile);
    } else if (curr_tile->isAdjacent(prev_tile)){
      tile_q.pop_back();
      curr_tile->swapOccupation(prev_tile);
    }
  }
  Render();
};

 //bool GameBoard::is_adjacent() {
 //  bool flag = false;
 //  Tile::Tile *tile_one =
 //      horizontal_board[xxx.at(0).first][xxx.at(0).second].get();
 //  Tile::Tile *tile_two =
 //      horizontal_board[xxx.at(1).first][xxx.at(1).second].get();

 //  if (tile_one->getHorzCoords().first ==
 //      tile_two->getHorzCoords().first) {
 //    flag = abs(tile_one->getHorzCoords().second -
 //               tile_two->getHorzCoords().second) == 1;
 //  }
 //  else if (tile_one->getVertCoords().first ==
 //      tile_two->getVertCoords().first) {
 //    flag = abs(tile_one->getVertCoords().second -
 //               tile_two->getVertCoords().second) == 1;
 //  }
 //  return flag;
 //};

//void GameBoard::Notified(Tile::TileCoord h_coords) {
//  std::cout << xxx.size() << std::endl;
//  std::cout << "Notified " << h_coords.first << " , " << h_coords.second
//            << std::endl;
//
//  Tile::Tile *new_tile =
//      horizontal_board[h_coords.first][h_coords.second].get();
//
//  if (xxx.size() == 0) {
//    if (horizontal_board[h_coords.first][h_coords.second]->getOccupation() !=
//        Tile::Occupation::NONE) {
//      xxx.push_back(h_coords);
//    }
//  } else {
//    Tile::Tile *prev_tile =
//        horizontal_board[xxx.at(0).first][xxx.at(0).second].get();
//    if (new_tile->getOccupation() != Tile::Occupation::NONE) {
//      xxx.pop_back();
//      xxx.push_back(h_coords);
//    } else {
//      xxx.push_back(h_coords);
//      if (is_adjacent()) {
//        xxx.pop_back();
//        xxx.pop_back();
//        new_tile->setOccupation(prev_tile->getOccupation());
//        prev_tile->setOccupation(Tile::Occupation::NONE);
//      } else {
//        xxx.pop_back();
//      }
//    }
//  }
//  Render();
//};

// void GameBoard::Update(sf::Event event) {
//   // if (event.type == sf::Event::MouseButtonReleased &&
//   //     event.mouseButton.button == sf::Mouse::Left) {
//   //   int i = 0;
//   //   int j = 0;
//   //   bool flag = false;
//   //   Tile::Tile *tile;
//   //
//   //   while (i < 8 && !flag) {
//   //     while (j < 3 && !flag) {
//   //       tile = horizontal_board[i][j].get();
//   //       if (tile->contains(event.mouseButton.x, event.mouseButton.y)) {
//   //         Notified(std::make_pair(i, j));
//   //         flag = true;
//   //       }
//   //       j++;
//   //     }
//   //     i++;
//   //   }
//   // }
// }
