#include "GameScene.hpp"

#include <iostream>
#include <memory>

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "../GameBoard.hpp"
#include "../Token.hpp"

GameScene::~GameScene() {}

GameScene::GameScene()
    : m_SaveButton{"Save",
                   [&](sf::Event e) { m_SaveButton.setText("Test Save"); }},
      m_QuitButton{"Quit", [&](sf::Event e) { m_IsKilled = true; }},
      m_GameBoard(std::make_unique<GameBoard>()) {
  AssetManager& assMan = AssetManager::GetInstance();
  m_SaveButton.setTexture(assMan.GetTexture(GameAsset::BUTTON).get());
  m_SaveButton.setPosition(sf::Vector2f(799.f, 916.f));

  m_QuitButton.setTexture(assMan.GetTexture(GameAsset::BUTTON).get());
  m_QuitButton.setPosition(sf::Vector2f(51.f, 909.f));

  m_PlayerOneText.setFont(*assMan.GetFont(GameAsset::COMFORTAA).get());
  m_PlayerOneText.setString("Pepe");
  m_PlayerOneText.setCharacterSize(32);
  m_PlayerOneText.setPosition(sf::Vector2f(332.f, 815.f));

  m_PlayerTwoText.setFont(*assMan.GetFont(GameAsset::COMFORTAA).get());
  m_PlayerTwoText.setString("Doge");
  m_PlayerTwoText.setCharacterSize(32);
  m_PlayerTwoText.setPosition(sf::Vector2f(687.f, 815.f));

  m_TurnText.setFont(*assMan.GetFont(GameAsset::COMFORTAA).get());
  m_TurnText.setString("Player 2 Move Token");
  m_TurnText.setCharacterSize(48);
  m_TurnText.setPosition(sf::Vector2f(313.f, 42.f));

  addDrawable(&m_PlayerOneText);
  addDrawable(&m_PlayerTwoText);
  addDrawable(&m_TurnText);

  m_PlayerOneIcon.setSize(sf::Vector2f(90, 90));
  m_PlayerTwoIcon.setSize(sf::Vector2f(90, 90));
  m_TurnIcon.setSize(sf::Vector2f(115, 115));

  m_PlayerOneIcon.setTexture(assMan.GetTexture(GameAsset::Texture::PEPE).get());
  m_PlayerTwoIcon.setTexture(assMan.GetTexture(GameAsset::Texture::DOGE).get());
  m_TurnIcon.setTexture(assMan.GetTexture(GameAsset::Texture::DOGE).get());

  m_PlayerOneIcon.setPosition(sf::Vector2f(213, 790));
  m_PlayerTwoIcon.setPosition(sf::Vector2f(567, 790));
  m_TurnIcon.setPosition(sf::Vector2f(157, 15));

  addDrawable(&m_PlayerOneIcon);
  addDrawable(&m_PlayerTwoIcon);
  addDrawable(&m_TurnIcon);

  addUI(&m_SaveButton);
  addUI(&m_QuitButton);
}

void GameScene::Update(sf::Event event) {
  Scene::Update(event);
  if (m_IsKilled) {
    Game::GetInstance().PopScene();
    return;
  }
  m_GameBoard->Update(event);
  // TODO : Make dynamic string for this
  m_TurnText.setString(m_GameBoard->GetCurrPlayer()->occupation ==
                               Token::Occupation::PEPE
                           ? "Player Pepe"
                           : "Player Doge");
}

void GameScene::Render(sf::RenderWindow& window) {
  Scene::Render(window);
  m_GameBoard->Render(window);
}
