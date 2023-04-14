#include "GameBoard.hpp"

#include <iostream>

#include "Game.hpp"
#include "Tile.hpp"

void GameBoard::Update(sf::Event event) {}
void GameBoard::Render() {
  sf::RenderWindow& window = Game::GetWindow();
  window.draw(m_Board);

  for (const auto& tile : m_Tiles) {
    if (tile.second.occupation != Tile::Occupation::NONE) {
      const sf::Color colour = tile.second.occupation == Tile::Occupation::DOGE
                                   ? sf::Color::Yellow
                                   : sf::Color::Green;
      m_DebugToken.setPosition(tile.second.coords);
      m_DebugToken.setFillColor(colour);
      window.draw(m_DebugToken);
    }
  }
}
GameBoard::GameBoard() : m_Board(sf::Vector2f(509.f, 542.f)) {
  m_DebugToken.setRadius(20.f);

  m_Board.setPosition(sf::Vector2f(184.f, 171.f));
  if (!m_BoardTexture.loadFromFile("assets/ui/Board.png")) {
    std::cerr << "Could not load Board Texture!" << std::endl;
  }
  m_Board.setTexture(&m_BoardTexture);
  InitialiseTiles();
}

void GameBoard::InitialiseTiles() {
  for (int y = 0; y < 7; y++) {
    // Is in the middle of the board.
    int width = (y == 3) ? 6 : 3;
    for (int x = 0; x < width; x++) {
      m_Tiles[std::make_pair(x, y)] =
          Tile::Tile{sf::Vector2f(x * 50, y * 50), std::make_pair(x, y),
                     Tile::Occupation::DOGE};
    }
  }
}

GameBoard::~GameBoard() {}
