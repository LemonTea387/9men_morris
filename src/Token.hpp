#ifndef TOKEN_H
#define TOKEN_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"

/**
 * The Token represents the token that a player places/moves/captures in a 9
 * Men's Morris game. It is placed in Tile, and should NOT exist on
 * its own if not associated with a Tile. It contains the textures that
 * represents the occupation of the player, as well as certain states to allow
 * customization on aesthetics of the Token. As such, it should generally not
 * contain any sort of game logic, but just a glorified drawable.
 */
class Token : public sf::Drawable, public sf::Transformable {
 public:
  /**
   * The Occupation or the player's enum values
   */
  enum Occupation { DOGE, PEPE };

  /**
   * The State the token is in, this can be used to configure the Token's
   * texture or aesthetics based on its state
   */
  enum TokenState { NORMAL, SCREAM, SUNGLASSES };

  /**
   * The Constructor for Token, position is a parameter that is usually related
   * to position of the Tile the Token is associated to.
   */
  Token(Token::Occupation occupation, const sf::Vector2f& position);

  /**
   * The Destructor for Token.
   */
  ~Token();

  /**
   * Setter for setting the state of the Token, this allows control over the
   * texture/aesthetics of the Token based on the state.
   */
  void SetState(TokenState state);

  /**
   * Setter for position to draw the Token at.
   */
  void SetPosition(const sf::Vector2f& position);

  /**
   * Get the occupation of the Token, or which player this Token belongs to.
   */
  Occupation GetOccupation();

 private:
  /**
   * The underlying Rectangle object that texture draws on.
   */
  sf::RectangleShape m_Rectangle;

  /**
   * The diffeent textures a token can have, normal state, scream state, and happy state. 
   * If there are more, would consider a lookup table/map
   */
  sf::Texture* m_NormalTexture;
  sf::Texture* m_ScreamTexture;
  sf::Texture* m_HappyTexture;

  /**
   * Occupation attribute of Token. This can technically be marked as const, but
   * may be reserved for any changes that may bring in differing game rules that
   * wants a job change.
   */
  Occupation m_Occupation;

  /**
   * State for controlling the aesthetics of the Token.
   */
  TokenState m_State{TokenState::NORMAL};

  /**
   * Draw function for being a sf::Drawable, this allows Token to be drew
   * directly from a RenderWindow context with `window.draw(token)`
   */
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

#endif
