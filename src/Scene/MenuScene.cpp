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

  m_TitleBackground.setFillColor(sf::Color(0x21, 0x1f, 0x26));
  m_TitleBackground.setSize(sf::Vector2f(478.f, 94.f));
  m_TitleBackground.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH / 5.f, Game::WINDOW_HEIGHT / 7.f));
  addDrawable(&m_TitleBackground);

  const auto textColor = sf::Color(0xE6, 0xE0, 0xE9);

  m_TitleText.setString("Nine Men's Morris");
  m_TitleText.setCharacterSize(32);
  m_TitleText.setFillColor(textColor);
  m_TitleText.setFont(*assMan.GetFont(GameAsset::Font::COMFORTAA));
  m_TitleText.setPosition(sf::Vector2f(Game::WINDOW_WIDTH / 5.f + 90.f,
                                       Game::WINDOW_HEIGHT / 7.f + 30.f));
  addDrawable(&m_TitleText);

  m_CopyrightNotice.setString("(C) Copyright 2023 All Rights Reserved");
  m_CopyrightNotice.setCharacterSize(20);
  m_CopyrightNotice.setFillColor(sf::Color(0xCA, 0xC4, 0xD0));
  m_CopyrightNotice.setFont(*assMan.GetFont(GameAsset::Font::ROBOTO_REGULAR));
  m_CopyrightNotice.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH / 20.f, Game::WINDOW_HEIGHT / 7.f * 6.f));
  addDrawable(&m_CopyrightNotice);

  m_CopyrightHolder.setString("The Everything Team");
  m_CopyrightHolder.setCharacterSize(20);
  m_CopyrightHolder.setFillColor(sf::Color(0xCA, 0xC4, 0xD0));
  m_CopyrightHolder.setFont(*assMan.GetFont(GameAsset::Font::ROBOTO_BOLD));
  m_CopyrightHolder.setPosition(sf::Vector2f(
      Game::WINDOW_WIDTH / 20.f, Game::WINDOW_HEIGHT / 7.f * 6.f + 25.f));
  addDrawable(&m_CopyrightHolder);
}
MenuScene::~MenuScene() {}
