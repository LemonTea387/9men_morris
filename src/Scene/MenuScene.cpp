#include "MenuScene.hpp"

#include <iostream>

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "GameScene.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
void MenuScene::Update(sf::Event event) { Scene::Update(event); }

void MenuScene::Render(sf::RenderWindow& window) { Scene::Render(window); }

MenuScene::MenuScene()
    : m_DogeVsPepe{sf::Vector2f(235.f, 115.f)},
      m_NewGameButton{
          "New Game",
          [&](sf::Event e) {
            Game::GetInstance().PushScene(std::make_unique<GameScene>());
          }},
      m_CreditsButton{"Credits", [&](sf::Event e) {}},
      m_ExitButton{"Quit",
                   [&](sf::Event e) { Game::GetInstance().PopScene(); }} {
  AssetManager& assMan = AssetManager::GetInstance();
  m_NewGameButton.setPosition(sf::Vector2f(319.f, 303.f));
  m_NewGameButton.setTexture(
      assMan.GetTexture(GameAsset::BUTTON_NEWGAME).get());
  m_CreditsButton.setPosition(sf::Vector2f(342.f, 415.f));
  m_CreditsButton.setTexture(assMan.GetTexture(GameAsset::BUTTON).get());
  m_ExitButton.setPosition(sf::Vector2f(367.f, 535.f));
  m_ExitButton.setTexture(assMan.GetTexture(GameAsset::BUTTON).get());
  m_DogeVsPepe.setPosition(sf::Vector2f(602.f, 728.f));

  addUI(&m_NewGameButton);
  addUI(&m_CreditsButton);
  addUI(&m_ExitButton);

  if (!m_DogeVsPepeTexture.loadFromFile("assets/ui/buttons/DogeVsPepe.png")) {
    std::cerr << "Could not load DogeVsPepe!" << std::endl;
  }
  m_DogeVsPepe.setTexture(&m_DogeVsPepeTexture);
  addDrawable(&m_DogeVsPepe);
}
MenuScene::~MenuScene() {}
