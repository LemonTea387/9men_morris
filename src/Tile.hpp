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
  Tile(GameBoard*, TileCoord coord);
  ~Tile();
  void SetHighlight(bool highlight);
  bool HasToken() const { return m_Token != nullptr; };
  Token* GetToken() const { return m_Token.get(); };
  void SetToken(std::unique_ptr<Token> token) { m_Token = std::move(token); };
  void MoveToken(Tile* dstTile) {
    m_Token->SetPosition(dstTile->getPosition());
    dstTile->SetToken(std::move(m_Token));
    m_Token = nullptr;
  };
  void RemoveToken() { m_Token = nullptr; };

  // TO-DO: Friend class MillObserver?
  TileCoord GetTileCoord() const { return m_Coord; }

 private:
  const sf::Texture* m_DefaultTexture;
  const sf::Texture* m_HighlightTexture;
  GameBoard* m_Gameboard;
  std::unique_ptr<Token> m_Token{nullptr};
  const TileCoord m_Coord;
  bool m_Highlight{false};
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};
#endif
