#include "WinScene.hpp"

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "../Scene/MenuScene.hpp"
#include "SFML/Window/Event.hpp"

void WinScene::Update(sf::Event event) {
  if (event.type == sf::Event::MouseButtonReleased) {
    for (auto& e : m_ui) {
      e->notifyListeners(event);
    }
  }
}
void WinScene::Render() {
  sf::RenderWindow& window = Game::GetWindow();

  for (auto& e : m_ui) {
    window.draw(*e);
  }

  for (auto& e : m_draw) {
    window.draw(*e);
  }
}

WinScene::WinScene(PlayerType pt)
    : m_PlaceholderButton("Main Menu", [&](sf::Event e) {
        Game::GetInstance().PushScene(std::make_unique<MenuScene>());
      }) {
  AssetManager& assMan = AssetManager::GetInstance();
  addUI(&m_PlaceholderButton);
  m_PlaceholderButton.setTexture(*assMan.GetTexture(GameAsset::BUTTON));
  m_PlaceholderButton.setPosition(sf::Vector2f(89.f, 916.f));
}
WinScene::~WinScene() {}
