#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace GameAsset {
enum Texture { DOGE, PEPE, NONE };
}
class AssetManager {
 private:
  typedef std::shared_ptr<sf::Texture> TexturePtr;
  std::map<GameAsset::Texture, TexturePtr> m_Textures;
  AssetManager();
  ~AssetManager();

  void LoadTextures();

 public:
  AssetManager(AssetManager const&) = delete;

  std::shared_ptr<sf::Texture> GetTexture(GameAsset::Texture) const;

  void operator=(const AssetManager&) = delete;

  static AssetManager& GetInstance() {
    static AssetManager instance;
    return instance;
  }
};

#endif
