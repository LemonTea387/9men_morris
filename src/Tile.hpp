#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include <memory>

#include "Scene/ui/Button.hpp"
#include "Token.hpp"

class GameBoard;

typedef std::pair<int, int> TileCoord;

class Tile : public graphics::Button {
 public:
  Tile(GameBoard*, TileCoord coord);
  ~Tile();
  Token* GetToken() const;
  bool HasToken() const;
  void RemoveToken();
  void SetHighlight(bool highlight);
  void SetToken(std::unique_ptr<Token> token);
  void MoveToken(Tile* dstTile);

  TileCoord GetTileCoord() const;

 private:
  bool m_Highlight{false};
  GameBoard* m_Gameboard;
  const TileCoord m_Coord;
  const sf::Texture* m_DefaultTexture;
  const sf::Texture* m_HighlightTexture;
  std::unique_ptr<Token> m_Token{nullptr};
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};
#endif
