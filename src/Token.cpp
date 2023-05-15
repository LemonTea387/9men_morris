#include "Token.hpp"

#include "AssetManager.hpp"
#include <iostream>

Token::Token(Occupation occupation, const sf::Vector2f& position) : m_Occupation{occupation}{
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
    m_Rectangle.setTexture(texture);
    m_Rectangle.setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
    m_Rectangle.setPosition(sf::Vector2f{position.x, position.y});
  }
}

Token::~Token() {}

void Token::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_Rectangle);
}