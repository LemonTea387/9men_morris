#include "MenuScene.hpp"

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "CreditsScene.hpp"
#include "GameScene.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
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
      m_CreditsButton{
          "Credits",
          [&](sf::Event e) {
            Game::GetInstance().PushScene(std::make_unique<CreditsScene>());
          }},
      m_ExitButton{"Quit",
                   [&](sf::Event e) { Game::GetInstance().PopScene(); }} {
  AssetManager& assMan = AssetManager::GetInstance();
  m_NewGameButton.setTexture(
      assMan.GetTexture(GameAsset::BUTTON_NEWGAME).get());
  m_CreditsButton.setTexture(assMan.GetTexture(GameAsset::BUTTON).get());
  m_ExitButton.setTexture(assMan.GetTexture(GameAsset::BUTTON).get());
  m_DogeVsPepe.setTexture(assMan.GetTexture(GameAsset::DOGE_VS_PEPE).get());

  // TODO : Button has extra padding at the right, FIX
  m_NewGameButton.setPosition(sf::Vector2f(
      Game::WINDOW_WIDTH * 0.5 - m_NewGameButton.getSize().x / 2 + 15., Game::WINDOW_HEIGHT*0.35));
  m_CreditsButton.setPosition(sf::Vector2f(
      Game::WINDOW_WIDTH * 0.5 - m_CreditsButton.getSize().x / 2 + 10., Game::WINDOW_HEIGHT*0.45));
  m_ExitButton.setPosition(sf::Vector2f(
      Game::WINDOW_WIDTH * 0.5 - m_ExitButton.getSize().x / 2 + 30., Game::WINDOW_HEIGHT*0.55));
  m_DogeVsPepe.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.7, Game::WINDOW_HEIGHT * 0.8));

  addUI(&m_NewGameButton);
  addUI(&m_CreditsButton);
  addUI(&m_ExitButton);

  addDrawable(&m_DogeVsPepe);

  // Title and title background
  const auto textColor = sf::Color(0xE6, 0xE0, 0xE9);
  m_TitleText.setString("Nine Men's Morris");
  m_TitleText.setCharacterSize(32);
  m_TitleText.setFillColor(textColor);
  m_TitleText.setFont(*assMan.GetFont(GameAsset::Font::COMFORTAA));
  m_TitleText.setPosition(sf::Vector2f(
      Game::WINDOW_WIDTH * 0.5 - m_TitleText.getLocalBounds().width / 2,
      Game::WINDOW_HEIGHT * 0.15));
  m_TitleBackground.setFillColor(sf::Color(0x21, 0x1f, 0x26));
  m_TitleBackground.setSize(
      sf::Vector2f(m_TitleText.getLocalBounds().width * (1 + 2 / 3.f),
                   m_TitleText.getLocalBounds().height * 4));
  m_TitleBackground.setPosition(sf::Vector2f(
      Game::WINDOW_WIDTH * 0.5 -
          m_TitleText.getLocalBounds().width * (0.5 + 1 / 3.f),
      Game::WINDOW_HEIGHT * 0.15 - m_TitleText.getLocalBounds().height));

  addDrawable(&m_TitleBackground);
  addDrawable(&m_TitleText);

  // Copyright texts
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
