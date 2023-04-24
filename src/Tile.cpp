#include "Tile.hpp"

namespace Tile{
	void Tile::Tile::set_horizontal_coords(int x, int y) {
		horizontal_coords = std::make_pair(x, y);
	}

	void Tile::Tile::set_vertical_coords(int x, int y) {
		vertical_coords = std::make_pair(x, y);
    }

	Occupation Tile::Tile::get_occupation() { return occupation;}

	void Tile::Tile::set_occupation(Occupation my_occupation) {
		occupation = my_occupation;
        sf::Texture myTexture;
        if (occupation == Occupation::DOGE) {
          if (!myTexture.loadFromFile("assets/ui/buttons/Doge.png")) {
            std::cerr << "Could not load UI button!" << std::endl;
          }
        } else if (occupation == Occupation::PEPE) {
          if (!myTexture.loadFromFile("assets/ui/buttons/Pepe.png")) {
            std::cerr << "Could not load UI button!" << std::endl;
          }
        } else if (occupation == Occupation::NONE) {
          if (!myTexture.loadFromFile("assets/ui/buttons/EmptyToken.png")) {
            std::cerr << "Could not load UI button!" << std::endl;
          }
        }

        setTexture(myTexture);
	}
}