#include "GameBoard.hpp"

#include <iostream>

#include "Game.hpp"
#include "Tile.hpp"

void GameBoard::Update(sf::Event event) {
  // if (event.type == sf::Event::MouseButtonReleased &&
  //     event.mouseButton.button == sf::Mouse::Left) {
  //   int i = 0;
  //   int j = 0;
  //   bool flag = false;
  //   Tile::Tile *tile;
  //
  //   while (i < 8 && !flag) {
  //     while (j < 3 && !flag) {
  //       tile = horizontal_board[i][j].get();
  //       if (tile->contains(event.mouseButton.x, event.mouseButton.y)) {
  //         Notified(std::make_pair(i, j));
  //         flag = true;
  //       }
  //       j++;
  //     }
  //     i++;
  //   }
  // }
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
  /* m_DebugToken.setRadius(20.f);*/
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      horizontal_board[i][j] = std::make_unique<Tile::Tile>(this);
    }
  }

  m_Board.setPosition(sf::Vector2f(223.f, 173.f));
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
      {{0, 0}, {0, 0}}, {{0, 1}, {3, 0}}, {{0, 2}, {7, 0}}, {{1, 0}, {1, 0}},
      {{1, 1}, {3, 1}}, {{1, 2}, {6, 0}}, {{2, 0}, {2, 0}}, {{2, 1}, {3, 2}},
      {{2, 2}, {5, 0}}, {{3, 0}, {0, 1}}, {{3, 1}, {1, 1}}, {{3, 2}, {2, 1}},
      {{4, 0}, {5, 0}}, {{4, 1}, {6, 1}}, {{4, 2}, {7, 1}}, {{5, 0}, {2, 2}},
      {{5, 1}, {4, 0}}, {{5, 2}, {5, 2}}, {{6, 0}, {1, 2}}, {{6, 1}, {4, 1}},
      {{6, 2}, {6, 2}}, {{7, 0}, {0, 2}}, {{7, 1}, {4, 2}}, {{7, 2}, {7, 2}}};

  int k;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      k = i * 3 + j;
      new_tile = horizontal_board[i][j].get();
      new_tile->set_horizontal_coords(coordinates[k][0][0],
                                      coordinates[k][0][1]);
      new_tile->set_vertical_coords(coordinates[k][1][0], coordinates[k][1][1]);
      new_tile->setPosition(sf::Vector2f(tile_pos[k][0], tile_pos[k][1]));
      new_tile->setSize(sf::Vector2f(72, 78));
      new_tile->set_occupation(Tile::Occupation::DOGE);
      // new_tile->set_occupation(Tile::Occupation::PEPE);
      // new_tile->set_occupation(Tile::Occupation::NONE);

      if (k < 9) {
        new_tile->set_occupation(Tile::Occupation::DOGE);
      } else if (k < 18) {
        new_tile->set_occupation(Tile::Occupation::PEPE);
      } else {
        new_tile->set_occupation(Tile::Occupation::NONE);
      }
    }
  }
}

GameBoard::~GameBoard() {}

bool GameBoard::is_adjacent() {
  bool flag = false;
  if (xxx.at(0).first == xxx.at(1).first) {
    flag = abs(xxx.at(0).second - xxx.at(1).second) == 1;
  } else if (xxx.at(0).first == xxx.at(1).first) {
    flag = abs(xxx.at(0).second - xxx.at(1).second) == 1;
  }
  return flag;
};

void GameBoard::Notified(Tile::TileCoord h_coords) {
  std::cout << xxx.size() << std::endl;
  std::cout << "Notified " << h_coords.first << " , " << h_coords.second
            << std::endl;
  Tile::Tile *new_tile =
      horizontal_board[h_coords.first][h_coords.second].get();

  if (xxx.size() == 0) {
    if (horizontal_board[h_coords.first][h_coords.second]->get_occupation() !=
        Tile::Occupation::NONE) {
      xxx.push_back(h_coords);
    }
  } else {
    Tile::Tile *prev_tile =
        horizontal_board[xxx.at(0).first][xxx.at(0).second].get();
    if (new_tile->get_occupation() != Tile::Occupation::NONE) {
      xxx.pop_back();
      xxx.push_back(h_coords);
    } else {
      xxx.push_back(h_coords);
      if (is_adjacent()) {
        xxx.pop_back();
        xxx.pop_back();
        new_tile->set_occupation(prev_tile->get_occupation());
        prev_tile->set_occupation(Tile::Occupation::NONE);
      } else {
        xxx.pop_back();
      }
    }
  }
  Render();
};
