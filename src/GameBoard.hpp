#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include <array>
#include <memory>

#include "GameObject.hpp"
#include "SFML/Graphics/CircleShape.hpp"

namespace Tile {
class Tile;
typedef std::pair<int, int> TileCoord;
}  // namespace Tile
class GameBoard : public GameObject {
 protected:
  std::array<std::array<std::unique_ptr<Tile::Tile>, 3>, 8> horizontal_board;
  std::array<std::array<std::unique_ptr<Tile::Tile>, 3>, 8> vertical_board;

  sf::RectangleShape m_Board;
  sf::Texture m_BoardTexture;

  sf::CircleShape m_DebugToken;
  std::vector<Tile::TileCoord> xxx;
  std::vector<Tile::Tile*> tile_q;
  Tile::Tile* new_tile;

  void InitialiseTiles();

 public:
  void Update(sf::Event event);
  void Render();
  GameBoard();
  ~GameBoard();
  //void Notified(Tile::TileCoord);
  void Notify(Tile::Tile*);
  bool is_adjacent();

  friend class PlaceCommand;
  friend class GameScene;
};

#endif
