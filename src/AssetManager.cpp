#include "AssetManager.hpp"

#include <iostream>

#include "SFML/Graphics/Texture.hpp"

// Anonymous namespace
namespace {
typedef std::pair<int, std::string> AssetFilePair;
typedef std::vector<AssetFilePair> AssetFilePairList;
const AssetFilePairList textures = {
    {GameAsset::Texture::DOGE, "assets/ui/buttons/Doge.png"},
    {GameAsset::Texture::PEPE, "assets/ui/buttons/Pepe.png"},
    {GameAsset::Texture::NONE, "assets/ui/buttons/coconut.png"}};
}  // namespace

std::shared_ptr<sf::Texture> AssetManager::GetTexture(
    GameAsset::Texture t) const {
  return m_Textures.at(t);
}
void AssetManager::LoadTextures() {
  for (const auto& pair : textures) {
    TexturePtr t = std::make_unique<sf::Texture>();
    if (!t->loadFromFile(pair.second)) {
      std::cerr << "Could not load texture: " << pair.second << std::endl;
    }
    m_Textures.insert({(GameAsset::Texture)(pair.first), std::move(t)});
  }
}

AssetManager::AssetManager() { LoadTextures(); }
AssetManager::~AssetManager() {}
