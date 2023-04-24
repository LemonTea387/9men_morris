#include "Tile.hpp"

#include <iostream>

#include "AssetManager.hpp"
#include "GameBoard.hpp"

namespace Tile {
Tile::Tile(GameBoard* gb) : m_Gameboard(gb), graphics::Button("") {
  this->setCallback([&](sf::Event event) {
    std::cout << "CLICK" << std::endl;
    gb->Notified(this->horizontal_coords);
  });
};

Tile::~Tile(){};

void Tile::Tile::set_horizontal_coords(int x, int y) {
  horizontal_coords = std::make_pair(x, y);
}

void Tile::Tile::set_vertical_coords(int x, int y) {
  vertical_coords = std::make_pair(x, y);
}

Occupation Tile::Tile::get_occupation() { return occupation; }

void Tile::Tile::set_occupation(Occupation my_occupation) {
  AssetManager& assMan = AssetManager::GetInstance();
  occupation = my_occupation;
  GameAsset::Texture myTexture;
  switch (occupation) {
    case Occupation::DOGE:
      myTexture = GameAsset::Texture::DOGE;
      break;
    case Occupation::PEPE:
      myTexture = GameAsset::Texture::PEPE;
      break;
    case Occupation::NONE:
      myTexture = GameAsset::Texture::EMPTY;
      break;
    default:
      break;
  }

  setTexture(*assMan.GetTexture(myTexture));
}

TileCoord Tile::Tile::get_horizontal_coords() { return horizontal_coords; };

TileCoord Tile::Tile::get_vertical_coords() { return vertical_coords; };

bool Tile::Tile::contains(int x, int y) {
  float x_start = getPosition().x;
  float y_start = getPosition().y;
  float width = getSize().x;
  float height = getSize().y;

  return x >= x_start && x <= x_start + width && y >= y_start &&
         y <= y_start + height;
}
}  // namespace Tile
