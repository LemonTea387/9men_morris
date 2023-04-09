#include "MenuScene.hpp"

#include "../Game.hpp"
#include "SFML/System/Vector2.hpp"
void MenuScene::Update(sf::Event event) {
  if (event.type == sf::Event::MouseButtonReleased &&
      event.mouseButton.button == sf::Mouse::Left) {
    if (m_QuitButton.getGlobalBounds().contains(event.mouseButton.x,
                                                event.mouseButton.y)) {
      Game::GetInstance().PopScene();
    }
  }
}

void MenuScene::Render() { Game::GetWindow().draw(m_QuitButton); }

MenuScene::MenuScene() : m_QuitButton(sf::Vector2f(191.f, 73.f)) {
  m_QuitButton.setPosition(354.f, 595.f);
}
MenuScene::~MenuScene() {}
