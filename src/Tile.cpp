#include "Tile.hpp"

#include <iostream>

#include "AssetManager.hpp"
#include "GameBoard.hpp"

namespace Tile {
Tile::Tile(GameBoard* gb) : m_Gameboard(gb), graphics::Button("") {
  this->setCallback(
      [&](sf::Event event) { m_Gameboard->Notify(this); });
};

Tile::~Tile(){};

void Tile::Tile::setHorzCoords(int x, int y) {
  horizontal_coords = std::make_pair(x, y);
}

void Tile::Tile::setVertCoords(int x, int y) {
  vertical_coords = std::make_pair(x, y);
}

Occupation Tile::Tile::getOccupation() { return occupation; }

void Tile::Tile::setOccupation(Occupation my_occupation) {
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
      myTexture = GameAsset::Texture::NONE;
      break;
    default:
      break;
  }

  setTexture(*assMan.GetTexture(myTexture));
}

TileCoord Tile::Tile::getHorzCoords() { return horizontal_coords; };

TileCoord Tile::Tile::getVertCoords() { return vertical_coords; };

bool Tile::isAdjacent(Tile* other) {
  bool flag = false;

  if (this->getHorzCoords().first == other->getHorzCoords().first) {
    flag = abs(this->getHorzCoords().second -
               other->getHorzCoords().second) == 1;
  } else if (this->getVertCoords().first == other->getVertCoords().first) {
    flag = abs(this->getVertCoords().second -
               other->getVertCoords().second) == 1;
  }
  
  return flag;
}

void Tile::swapOccupation(Tile* other) {
  Occupation temp = this->getOccupation();
  this->setOccupation(other->getOccupation());
  other->setOccupation(temp);
}


}  // namespace Tile
