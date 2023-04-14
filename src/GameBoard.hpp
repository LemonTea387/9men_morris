#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>

// TO DO: This has an Update and Render function. Maybe
// repurpose Scene class to a "GameObject" class?
class GameBoard {
 private:
  sf::RectangleShape m_Board;
  sf::Texture m_BoardTexture;

 public:
  void Update(sf::Event event);
  void Render();
  GameBoard();
  ~GameBoard();
};

#endif
