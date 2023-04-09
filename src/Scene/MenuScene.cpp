#include "MenuScene.hpp"

#include "../Game.hpp"
#include "SFML/System/Vector2.hpp"
void MenuScene::Update() {}

void MenuScene::Render() { Game::GetWindow().draw(m_QuitButton); }

MenuScene::MenuScene() : m_QuitButton(sf::Vector2f(120.f, 50.f)) {
  m_QuitButton.setPosition(20.f, 50.f);
}
MenuScene::~MenuScene() {}
