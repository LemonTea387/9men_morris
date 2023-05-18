#include "WinScene.hpp"

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

void WinScene::Update(sf::Event event) {
  if (event.type == sf::Event::MouseButtonReleased) {
    for (auto& e : m_ui) {
      e->notifyListeners(event);
    }
  }
}
void WinScene::Render(sf::RenderWindow& window) {
  window.draw(m_WinImage);
  window.draw(m_WinMessage);

  for (auto& e : m_ui) {
    window.draw(*e);
  }

  for (auto& e : m_draw) {
    window.draw(*e);
  }
}

WinScene::WinScene(WinnerType wt)
    : m_MenuButton("Main Menu", [&](sf::Event e) {
        Game::GetInstance().PopScene();
        Game::GetInstance().PopScene();
      }) {
  AssetManager& assMan = AssetManager::GetInstance();
  addUI(&m_MenuButton);
  m_WinMessage.setFont(*assMan.GetFont(GameAsset::Font::COMFORTAA));
  m_WinMessage.setFillColor(sf::Color(0xD0, 0xBC, 0xFF));
  m_WinMessage.setCharacterSize(64);

  sf::Texture* texture;
  const auto dogePos =
      sf::Vector2f(Game::WINDOW_WIDTH / 6.f, Game::WINDOW_HEIGHT / 3.f);
  const auto pepePos =
      sf::Vector2f(Game::WINDOW_WIDTH / 4.f, Game::WINDOW_HEIGHT / 4.f);
  const auto tiePos =
      sf::Vector2f(Game::WINDOW_WIDTH / 6.f, Game::WINDOW_HEIGHT / 3.f);

  switch (wt) {
    case WinnerType::DOGE:
      m_WinMessage.setString("Doge Wins!");
      texture = assMan.GetTexture(GameAsset::Texture::DOGEWIN).get();
      m_WinImage.setPosition(dogePos);
      break;
    case WinnerType::PEPE:
      m_WinMessage.setString("Pepe Wins!");
      texture = assMan.GetTexture(GameAsset::Texture::PEPEWIN).get();
      m_WinImage.setPosition(pepePos);
      break;
    case WinnerType::TIE:
      m_WinMessage.setString("It's a Tie!!!!");
      texture = assMan.GetTexture(GameAsset::Texture::TIEWIN).get();
      m_WinImage.setPosition(tiePos);
      break;
    default:
      break;
  }

  m_WinMessage.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH / 4.f, Game::WINDOW_HEIGHT / 10.f));
  m_WinImage.setTexture(texture);
  m_WinImage.setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
  m_MenuButton.setTexture(assMan.GetTexture(GameAsset::BUTTON).get());
  m_MenuButton.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH / 7.f,
                   Game::WINDOW_HEIGHT - Game::WINDOW_HEIGHT / 6.f));
}
WinScene::~WinScene() {}
