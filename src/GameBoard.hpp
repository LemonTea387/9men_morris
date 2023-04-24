#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "GameObject.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Tile.hpp"

class GameBoard : public GameObject{
 protected:
  typedef std::map<Tile::TileCoord, Tile::Tile> Tiles;
  Tiles m_Tiles;

  Tile::Tile horizontal_board[8][3];
  Tile::Tile vertical_board[8][3];

  sf::RectangleShape m_Board;
  sf::Texture m_BoardTexture;

  sf::CircleShape m_DebugToken;
  std::vector<Tile::TileCoord> xxx;

  void InitialiseTiles();

 public:
  void Update(sf::Event event);
  void Render();
  GameBoard();
  ~GameBoard();
  void Notified(Tile::TileCoord);
  bool is_adjacent();

  friend class PlaceCommand;
};

#endif
