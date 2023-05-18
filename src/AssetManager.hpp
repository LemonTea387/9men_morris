#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace GameAsset {
enum Texture {
  DOGE,
  DOGE_SUNGLASSES,
  DOGE_SCREAM,
  PEPE,
  PEPE_SUNGLASSES,
  PEPE_SCREAM,
  BUTTON,
  BUTTON_NEWGAME,
  BOARD,
  TILE,
  DOGE_VS_PEPE,
  HIGHLIGHT_TILE,
  PEPEWIN,
  DOGEWIN,
  TIEWIN
};
enum Font { COMFORTAA, ROBOTO_REGULAR, ROBOTO_BOLD };
}  // namespace GameAsset
class AssetManager {
 private:
  AssetManager();
  ~AssetManager();
  typedef std::shared_ptr<sf::Font> FontPtr;
  typedef std::shared_ptr<sf::Texture> TexturePtr;
  std::map<GameAsset::Texture, TexturePtr> m_Textures;
  std::map<GameAsset::Font, FontPtr> m_Fonts;
  void LoadFonts();
  void LoadTextures();

 public:
  AssetManager(AssetManager const&) = delete;
  void operator=(const AssetManager&) = delete;

  std::shared_ptr<sf::Font> GetFont(GameAsset::Font) const;
  std::shared_ptr<sf::Texture> GetTexture(GameAsset::Texture) const;
  static AssetManager& GetInstance() {
    static AssetManager instance;
    return instance;
  }
};

#endif
