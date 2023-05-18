#include "AssetManager.hpp"

#include <iostream>

#include "SFML/Graphics/Texture.hpp"

// Anonymous namespace
namespace {
typedef std::pair<int, std::string> AssetFilePair;
const std::vector<AssetFilePair> textures = {
    {GameAsset::Texture::DOGE, "assets/ui/buttons/Doge.png"},
    {GameAsset::Texture::DOGE_SUNGLASSES,
     "assets/ui/buttons/DogeSunglasses.png"},
    {GameAsset::Texture::DOGE_SCREAM, "assets/ui/buttons/DogeScream.png"},
    {GameAsset::Texture::PEPE, "assets/ui/buttons/Pepe.png"},
    {GameAsset::Texture::PEPE_SUNGLASSES,
     "assets/ui/buttons/PepeSunglasses.png"},
    {GameAsset::Texture::PEPE_SCREAM, "assets/ui/buttons/PepeCry.png"},
    {GameAsset::Texture::HIGHLIGHT_TILE, "assets/ui/buttons/coconut.png"},
    {GameAsset::Texture::TILE, "assets/ui/buttons/trns.png"},
    {GameAsset::Texture::DOGE_VS_PEPE, "assets/ui/buttons/DogeVsPepe.png"},
    {GameAsset::Texture::BUTTON, "assets/ui/buttons/Exit.png"},
    {GameAsset::Texture::BUTTON_NEWGAME, "assets/ui/buttons/NewGame.png"},
    {GameAsset::Texture::BOARD, "assets/ui/gameBoard.png"},
    {GameAsset::Texture::PEPEWIN, "assets/ui/PepeWin.png"},
    {GameAsset::Texture::DOGEWIN, "assets/ui/DogeWin.png"},
    {GameAsset::Texture::TIEWIN, "assets/ui/Tie.png"},
};
const std::vector<AssetFilePair> fonts = {
    {GameAsset::Font::COMFORTAA,
     "assets/fonts/Comfortaa/static/Comfortaa-SemiBold.ttf"},
    {GameAsset::Font::ROBOTO_REGULAR, "assets/fonts/Roboto/Roboto-Regular.ttf"},
    {GameAsset::Font::ROBOTO_BOLD, "assets/fonts/Roboto/Roboto-Bold.ttf"}};
}  // namespace

std::shared_ptr<sf::Texture> AssetManager::GetTexture(
    GameAsset::Texture t) const {
  return m_Textures.at(t);
}
std::shared_ptr<sf::Font> AssetManager::GetFont(GameAsset::Font t) const {
  return m_Fonts.at(t);
}

AssetManager::AssetManager() {
  LoadTextures();
  LoadFonts();
}

AssetManager::~AssetManager() {}

void AssetManager::LoadFonts() {
  for (const auto& pair : fonts) {
    FontPtr t = std::make_unique<sf::Font>();
    if (!t->loadFromFile(pair.second)) {
      std::cerr << "Could not load font: " << pair.second << std::endl;
    }
    m_Fonts.insert({(GameAsset::Font)(pair.first), std::move(t)});
  }
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
