#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace GameAsset {
enum Texture { DOGE, PEPE, BUTTON, BOARD, TILE, HIGHLIGHT_TILE };
enum Font { COMFORTAA };
}  // namespace GameAsset
class AssetManager {
 private:
  typedef std::shared_ptr<sf::Texture> TexturePtr;
  std::map<GameAsset::Texture, TexturePtr> m_Textures;
  typedef std::shared_ptr<sf::Font> FontPtr;
  std::map<GameAsset::Font, FontPtr> m_Fonts;
  AssetManager();
  ~AssetManager();

  void LoadTextures();
  void LoadFonts();

 public:
  AssetManager(AssetManager const&) = delete;

  std::shared_ptr<sf::Texture> GetTexture(GameAsset::Texture) const;
  std::shared_ptr<sf::Font> GetFont(GameAsset::Font) const;

  void operator=(const AssetManager&) = delete;

  static AssetManager& GetInstance() {
    static AssetManager instance;
    return instance;
  }
};

#endif
