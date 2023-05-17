#include "Token.hpp"

#include "AssetManager.hpp"
#include <iostream>

Token::Token(Occupation occupation, const sf::Vector2f& position)
    : m_Occupation{occupation} {
  // Obtain texture from AssetManager based on the occupation
  AssetManager& assMan = AssetManager::GetInstance();
  sf::Texture* texture = nullptr;
  switch (occupation) {
    case DOGE:
      texture = assMan.GetTexture(GameAsset::DOGE).get();
      break;
    case PEPE:
      texture = assMan.GetTexture(GameAsset::PEPE).get();
      break;
  }
  if (texture != nullptr) {
    // Only if texture is not a nullptr, prevent nullptr referencing.
    m_Rectangle.setTexture(texture);
    // Size of the rectangle be set to size of texture.
    m_Rectangle.setSize(
        sf::Vector2f(texture->getSize().x, texture->getSize().y));
    m_Rectangle.setPosition(sf::Vector2f{position.x, position.y});
  }
};

Token::~Token(){};

void Token::SetState(TokenState state) { m_State = state; };

void Token::SetPosition(const sf::Vector2f& position) {
  m_Rectangle.setPosition(position);
}

void Token::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // Draw the texture which is set on Rectangle
  target.draw(m_Rectangle);
};

Token::Occupation Token::GetOccupation() { return m_Occupation; };
