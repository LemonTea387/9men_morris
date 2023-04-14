#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>

#include "GameObject.hpp"

class GameBoard : public GameObject {
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
