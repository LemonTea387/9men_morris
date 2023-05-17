#include "Token.hpp"

#include "AssetManager.hpp"

Token::Token(Occupation occupation, const sf::Vector2f& position)
    : m_Occupation{occupation} {
  // Obtain texture from AssetManager based on the occupation
  AssetManager& assMan = AssetManager::GetInstance();
  switch (occupation) {
    case DOGE:
      m_NormalTexture = assMan.GetTexture(GameAsset::DOGE).get();
      m_ScreamTexture = assMan.GetTexture(GameAsset::DOGE_SCREAM).get();
      m_HappyTexture = assMan.GetTexture(GameAsset::DOGE_SUNGLASSES).get();
      break;
    case PEPE:
      m_NormalTexture = assMan.GetTexture(GameAsset::PEPE).get();
      m_ScreamTexture = assMan.GetTexture(GameAsset::PEPE_SCREAM).get();
      m_HappyTexture = assMan.GetTexture(GameAsset::PEPE_SUNGLASSES).get();
      break;
  }
  m_Rectangle.setTexture(m_NormalTexture);
  // Size of the rectangle be set to size of texture.
  m_Rectangle.setSize(
      sf::Vector2f(m_NormalTexture->getSize().x, m_NormalTexture->getSize().y));
  m_Rectangle.setPosition(sf::Vector2f{position.x, position.y});
};

Token::~Token(){};

void Token::SetState(TokenState state) {
  m_State = state;
  switch (state) {
    case NORMAL:
      m_Rectangle.setTexture(m_NormalTexture);
      break;
    case SCREAM:
      m_Rectangle.setTexture(m_ScreamTexture);
      break;
    case SUNGLASSES:
      m_Rectangle.setTexture(m_HappyTexture);
      break;
  }
};

void Token::SetPosition(const sf::Vector2f& position) {
  m_Rectangle.setPosition(position);
}

void Token::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // Draw the texture which is set on Rectangle
  target.draw(m_Rectangle);
};

Token::Occupation Token::GetOccupation() { return m_Occupation; };
