#ifndef TOKEN_H
#define TOKEN_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Transformable.hpp"

class Token : public sf::Drawable, public sf::Transformable {
 public:
  enum Occupation { DOGE, PEPE };
  enum TokenState { NORMAL, SCREAM, SUNGLASSES };
  Token(Token::Occupation occupation, const sf::Vector2f& position);
  ~Token();
  Occupation GetOccupation() { return m_Occupation; };
  void SetState(TokenState state) { m_State = state; }
  void SetPosition(const sf::Vector2f& position) {
    m_Rectangle.setPosition(position);
  }

 private:
  sf::RectangleShape m_Rectangle;
  Occupation m_Occupation;
  TokenState m_State{TokenState::NORMAL};
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

#endif
