#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include <memory>

#include "Scene/ui/Button.hpp"
#include "Token.hpp"

class GameBoard;
/**
 * TODO: Create class for TileCoord with proper bounds checkings.
 * Can  also possibly overload the hash function () operator / equality check
 * to use std::unordered_map for a tiny bit extra performance.
 */

typedef std::pair<int, int> TileCoord;

class Tile : public graphics::Button {
 public:
  Token* GetToken() const { return m_Token.get(); };
  bool HasToken() const { return m_Token != nullptr; };
  void RemoveToken() { m_Token = nullptr; };
  void SetHighlight(bool highlight);
  void SetToken(std::unique_ptr<Token> token) { m_Token = std::move(token); };
  void MoveToken(Tile* dstTile) {
    m_Token->SetPosition(dstTile->getPosition());
    dstTile->SetToken(std::move(m_Token));
    m_Token = nullptr;
  };

  Tile(GameBoard*, TileCoord coord);
  ~Tile();

  // TO-DO: Friend class MillObserver?
  TileCoord GetTileCoord() const { return m_Coord; }

 private:
  bool m_Highlight{false};
  const TileCoord m_Coord;
  const sf::Texture* m_DefaultTexture;
  const sf::Texture* m_HighlightTexture;
  GameBoard* m_Gameboard;
  std::unique_ptr<Token> m_Token{nullptr};
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};
#endif
