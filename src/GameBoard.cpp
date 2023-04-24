#include "GameBoard.hpp"

#include <iostream>

#include "Game.hpp"
#include "Tile.hpp"


void GameBoard::Update(sf::Event event) {}
void GameBoard::Render() {
  sf::RenderWindow& window = Game::GetWindow();
  window.draw(m_Board);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      window.draw(horizontal_board[i][j]);
    }
  }
    
}
GameBoard::GameBoard() : m_Board(sf::Vector2f(509.f, 542.f)) {
  /* m_DebugToken.setRadius(20.f);*/

  m_Board.setPosition(sf::Vector2f(223.f, 173.f));
  if (!m_BoardTexture.loadFromFile("assets/ui/gameBoard.png")) {
    std::cerr << "Could not load Board Texture!" << std::endl;
  }
  m_Board.setTexture(&m_BoardTexture);

  InitialiseTiles();
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
      {{6, 2}, {6, 2}}, {{7, 0}, {0, 2}}, {{7, 1}, {4, 2}}, {{7, 2}, {7, 2}}
  };

  for (int i = 0; i < 24; i++) {
    Tile::Tile new_tile;
    new_tile.set_occupation(Tile::Occupation::NONE);
    new_tile.set_horizontal_coords(coordinates[i][0][0], coordinates[i][0][1]);
    new_tile.set_vertical_coords(coordinates[i][1][0], coordinates[i][1][1]);
    new_tile.setPosition(sf::Vector2f(tile_pos[i][0], tile_pos[i][1]));
    new_tile.setSize(sf::Vector2f(72, 78));
    new_tile.setText("");
    horizontal_board[coordinates[i][0][0]][coordinates[i][0][1]] = new_tile;
    vertical_board[coordinates[i][1][0]][coordinates[i][1][1]] = new_tile;

    if (i < 9) {
        new_tile.set_occupation(Tile::Occupation::DOGE);
    } else if (i >= 24 - 1) {
        new_tile.set_occupation(Tile::Occupation::PEPE);
    }
  }


}

GameBoard::~GameBoard() {}
