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

  window.draw(m_WinImage);
  window.draw(m_WinMessage);

  for (auto& e : m_ui) {
    window.draw(*e);
  }

  for (auto& e : m_draw) {
    window.draw(*e);
  }
}

WinScene::WinScene(PlayerType pt)
    : m_MenuButton("Main Menu", [&](sf::Event e) {
        Game::GetInstance().PopScene();
        Game::GetInstance().PushScene(std::make_unique<MenuScene>());
      }) {
  AssetManager& assMan = AssetManager::GetInstance();
  addUI(&m_MenuButton);
  m_WinMessage.setFont(*assMan.GetFont(GameAsset::Font::COMFORTAA));
  m_WinMessage.setFillColor(sf::Color(0xD0, 0xBC, 0xFF));
  m_WinMessage.setCharacterSize(64);

  m_WinMessage.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH / 4.f, Game::WINDOW_HEIGHT / 10.f));
  m_WinMessage.setString(pt == PlayerType::PEPE ? "Player 1 Wins!"
                                                : "Player 2 Wins!");
  const auto winTexture = pt == PlayerType::DOGE
                              ? assMan.GetTexture(GameAsset::DOGEWIN)
                              : assMan.GetTexture(GameAsset::PEPEWIN);
  m_WinImage.setTexture(winTexture.get());
  m_WinImage.setSize(
      sf::Vector2f(winTexture->getSize().x, winTexture->getSize().y));
  const auto dogePos =
      sf::Vector2f(Game::WINDOW_WIDTH / 6.f, Game::WINDOW_HEIGHT / 3.f);
  const auto pepePos =
      sf::Vector2f(Game::WINDOW_WIDTH / 4.f, Game::WINDOW_HEIGHT / 4.f);
  m_WinImage.setPosition(pt == PlayerType::DOGE ? dogePos : pepePos);
  m_MenuButton.setTexture(*assMan.GetTexture(GameAsset::BUTTON));
  m_MenuButton.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH / 7.f,
                   Game::WINDOW_HEIGHT - Game::WINDOW_HEIGHT / 6.f));
}
WinScene::~WinScene() {}
