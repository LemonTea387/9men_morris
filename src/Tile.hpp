#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include <memory>

#include "Scene/ui/Button.hpp"
#include "Serializable.hpp"
#include "Token.hpp"

class GameBoard;

typedef std::pair<int, int> TileCoord;

/**
 * Tile is a clickable button that represents the tiles on a gameboard, it can
 * either have no Token on it or have one singular Token on it. Tile as a button
 * is the main way the player is able to interact with the game. The callback of
 * a particular Tile in a gameboard is usually to communicate with the GameBoard
 * or launch Commands that the GameBoard executes. Tile does not hold any
 * meaning if it exists without being in a GameBoard, so any dangling Tile is
 * effectively useless.
 */
class Tile : public graphics::Button, public Serializable {
 public:
  /**
   * Tile constructor, tile uses the gameboard pointer to communicate with the
   * gameboard directly. It also stores the coordinate of itself in the
   * gameboard.
   */
  Tile(GameBoard*, TileCoord coord);

  /**
   * Tile Destructor.
   */
  ~Tile();

  /**
   * Returns the Token pointer if there is a token and nullptr if there isn't,
   * usually used along with HasToken()
   */
  Token* GetToken() const;

  /**
   * Returns a check to see if Tile contains a Token
   */
  bool HasToken() const;

  /**
   * Removes the Token from the Tile, Token is effectively deleted.
   */
  std::unique_ptr<Token> RemoveToken();

  /**
   * Highlights the Tile, in gameplay context, this activates the Tile which
   * allows the Tile to launch Commands for the GameBoard to execute.
   */
  void SetHighlight(bool highlight);

  /**
   * Places a Token into the Tile, effectively claims the ownership of the
   * Token.
   */
  void SetToken(std::unique_ptr<Token> token);

  /**
   * Moves a Token from this Tile to the dstTile.
   */
  void MoveToken(Tile* dstTile);

  /**
   * Getter for obtaining the Tile Coordinates in a GameBoard.
   */
  TileCoord GetTileCoord() const;

  std::string serialize() override;

 private:
  /**
   * Highlight attribute to 'activate' the Tile to launch Commands for GameBoard
   * to execute.
   */
  bool m_Highlight{false};

  /**
   * Pointer to the GameBoard the Tile belongs to for communicating with the
   * GameBoard.
   */
  GameBoard* m_Gameboard;

  /**
   * The constant tile coordinates in the GameBoard, this does not change.
   */
  const TileCoord m_Coord;

  /**
   * Default Texture for the Tile (Not highlighted texture)
   */
  const sf::Texture* m_DefaultTexture;

  /**
   * Highlighted Texture for the Tile
   */
  const sf::Texture* m_HighlightTexture;

  /**
   * The Token on the Tile, can be nullptr which signifies no Token on the Tile.
   */
  std::unique_ptr<Token> m_Token{nullptr};

  /**
   * sf::Drawable draw function, allows Tile to be drawn with sf::RenderWindow
   * `window.draw(tile)`
   */
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};
#endif
