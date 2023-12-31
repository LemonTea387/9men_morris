#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

/**
 * The definition for all the GameAssets used in the application
 */
namespace GameAsset {
/**
 * Every Texture and their identifier
 */
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
/**
 * Every different Fonts and their identifier
 */
enum Font { COMFORTAA, ROBOTO_REGULAR, ROBOTO_BOLD };
}  // namespace GameAsset

/**
 * The AssetManager class that is responsible for loading all assets of the game
 * and readily provide them to use of such assets. AssetManager is a Singleton,
 * only one AssetManager should exist in the game so that it can manage all the
 * assets used. It loads the assets on start-up to make them readily available
 * throughout the life-time of the game.
 */
class AssetManager {
 private:
  /**
   * Privatised Constructor. The Constructor is set to private to ensure only 1
   * instance can be made (done via static method GetInstance as it has access
   * to private constructor and will only ever call the constructor once no
   * matter how many times it is called).
   */
  AssetManager();

  /**
   * Privatised Destructor. No particular reason for making this private, but
   * since the class is constructed in GetInstance() as a static member, it will
   * still be called on its destruction.
   */
  ~AssetManager();

  typedef std::shared_ptr<sf::Font> FontPtr;
  typedef std::shared_ptr<sf::Texture> TexturePtr;

  /**
   * Stores all the Texture identifier mapping to the loaded textures' pointers
   */
  std::map<GameAsset::Texture, TexturePtr> m_Textures;

  /**
   * Stores all the Font identifier mapping to the loaded fonts' pointers
   */
  std::map<GameAsset::Font, FontPtr> m_Fonts;

  /**
   * Loads all registered Font
   */
  void LoadFonts();

  /**
   * Loads all registered Texture
   */
  void LoadTextures();

 public:
  /**
   * Delete the copy constructor. We don't want to be able to have multiple
   * instances of the AssetManager, so we don't allow copying it.
   */
  AssetManager(AssetManager const&) = delete;

  /**
   * Deletes the assignment operator. Similarly to the copy constuctor, we don't
   * want to be able to assign the GetInstance() to any other object since we
   * only want a single instance of AssetManager to be available.
   */
  void operator=(const AssetManager&) = delete;

  /**
   * Gets the loaded Font based on the Font identifier
   */
  std::shared_ptr<sf::Font> GetFont(GameAsset::Font) const;

  /**
   * Gets the loaded Texture based on the Texture identifier
   */
  std::shared_ptr<sf::Texture> GetTexture(GameAsset::Texture) const;

  /**
   * Gets the global instance of the AssetManager. We only want a single
   * instance of the AssetManager. This static method is the only way to
   * retrieve it since only here can it call its own constructor since the
   * constructor is privated and thus inaccessible anywhere else.
   */
  static AssetManager& GetInstance() {
    static AssetManager instance;
    return instance;
  }
};

#endif
