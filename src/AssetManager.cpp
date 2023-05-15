#include "AssetManager.hpp"

#include <iostream>

#include "SFML/Graphics/Texture.hpp"

// Anonymous namespace
namespace {
typedef std::pair<int, std::string> AssetFilePair;
const std::vector<AssetFilePair> textures = {
    {GameAsset::Texture::DOGE, "assets/ui/buttons/Doge.png"},
    {GameAsset::Texture::PEPE, "assets/ui/buttons/Pepe.png"},
    {GameAsset::Texture::NONE, "assets/ui/buttons/coconut.png"},
    {GameAsset::Texture::BUTTON, "assets/ui/buttons/Exit.png"},
    {GameAsset::Texture::BOARD, "assets/ui/gameBoard.png"}};
const std::vector<AssetFilePair> fonts = {
    {GameAsset::Font::COMFORTAA,
     "assets/fonts/Comfortaa/static/Comfortaa-SemiBold.ttf"}};
}  // namespace

std::shared_ptr<sf::Texture> AssetManager::GetTexture(
    GameAsset::Texture t) const {
  return m_Textures.at(t);
}
std::shared_ptr<sf::Font> AssetManager::GetFont(GameAsset::Font t) const {
  return m_Fonts.at(t);
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
void AssetManager::LoadFonts() {
  for (const auto& pair : fonts) {
    FontPtr t = std::make_unique<sf::Font>();
    if (!t->loadFromFile(pair.second)) {
      std::cerr << "Could not load font: " << pair.second << std::endl;
    }
    m_Fonts.insert({(GameAsset::Font)(pair.first), std::move(t)});
  }
}

AssetManager::AssetManager() {
  LoadTextures();
  LoadFonts();
}
AssetManager::~AssetManager() {}
