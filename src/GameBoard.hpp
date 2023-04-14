#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "GameObject.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Tile.hpp"

class GameBoard : public GameObject {
 private:
  typedef std::map<Tile::TileCoord, Tile::Tile> Tiles;
  Tiles m_Tiles;
  sf::RectangleShape m_Board;
  sf::Texture m_BoardTexture;

  sf::CircleShape m_DebugToken;

  void InitialiseTiles();

 public:
  void Update(sf::Event event);
  void Render();
  GameBoard();
  ~GameBoard();

  friend class PlaceCommand;
};

#endif
