#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace GameAsset {
enum Texture { DOGE, PEPE, EMPTY };
}
class AssetManager {
 private:
  typedef std::unique_ptr<sf::Texture> TexturePtr;
  std::map<GameAsset::Texture, TexturePtr> m_Textures;
  AssetManager();
  ~AssetManager();

  void LoadTextures();

 public:
  AssetManager(AssetManager const&) = delete;
  void operator=(const AssetManager&) = delete;

  static AssetManager& GetInstance() {
    static AssetManager instance;
    return instance;
  }
};

#endif
