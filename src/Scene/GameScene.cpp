#include "GameScene.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "../GameBoard.hpp"
#include "../SaveGame.hpp"
#include "SaveScene.hpp"

namespace {
sf::Clock localClock;
}

GameScene::~GameScene() {}

GameScene::GameScene()
    : m_SaveButton{"Save"},
      m_UndoButton{"Undo", [&](sf::Event e) { m_GameBoard->UndoCommand(); }},
      m_QuitButton{"Quit",
                   [&](sf::Event e) {
                     // Marks the Scene to be popped and go back to previous
                     // Scene.
                     m_IsKilled = true;
                   }},
      m_GameBoard(std::make_unique<GameBoard>()) {
  m_SaveGame = std::make_unique<SaveGame>(m_GameBoard.get());

  m_SaveButton.setCallback([this](sf::Event e) {
    Game::GetInstance().PushScene(
        std::make_unique<SaveScene>(m_SaveGame.get()));
  });
  AssetManager& assMan = AssetManager::GetInstance();

  auto btnTexture = assMan.GetTexture(GameAsset::BUTTON).get();
  m_QuitButton.setTexture(btnTexture);
  m_SaveButton.setTexture(btnTexture);
  m_UndoButton.setTexture(btnTexture);

  // Quit and Save placed with 5% width on both sides, in lower 90% of height
  m_QuitButton.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.05, Game::WINDOW_HEIGHT * 0.9));
  // TODO : FIX the asset padding
  // The asset of button has slight padding, need to account for that in calc
  // Theory : it uses C string for width calculation, thus it can account for \0
  // character
  m_SaveButton.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.95 - m_SaveButton.getSize().x + 20.f,
                   Game::WINDOW_HEIGHT * 0.9));
  m_UndoButton.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.425, Game::WINDOW_HEIGHT * 0.9));

  auto font = assMan.GetFont(GameAsset::COMFORTAA).get();
  m_PlayerOneTexture = assMan.GetTexture(GameAsset::Texture::PEPE).get();
  m_PlayerTwoTexture = assMan.GetTexture(GameAsset::Texture::DOGE).get();

  m_TurnText.setFont(*font);
  m_PlayerOneText.setFont(*font);
  m_PlayerTwoText.setFont(*font);

  m_TurnText.setCharacterSize(48);
  m_PlayerOneText.setCharacterSize(32);
  m_PlayerTwoText.setCharacterSize(32);

  m_TurnText.setString("Pepe - Place");
  m_PlayerOneText.setString("Pepe");
  m_PlayerTwoText.setString("Doge");

  m_TurnIcon.setTexture(m_PlayerOneTexture);
  m_PlayerOneIcon.setTexture(m_PlayerOneTexture);
  m_PlayerTwoIcon.setTexture(m_PlayerTwoTexture);

  m_TurnIcon.setSize(sf::Vector2f(115, 115));
  m_PlayerOneIcon.setSize(sf::Vector2f(90, 90));
  m_PlayerTwoIcon.setSize(sf::Vector2f(90, 90));

  m_TurnText.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.4, Game::WINDOW_HEIGHT * 0.1 - 50));
  m_PlayerOneText.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.35, Game::WINDOW_HEIGHT * 0.85 - 50));
  m_PlayerTwoText.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.65, Game::WINDOW_HEIGHT * 0.85 - 50));
  m_TurnIcon.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.25, Game::WINDOW_HEIGHT * 0.05 - 50));
  m_PlayerOneIcon.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.25, Game::WINDOW_HEIGHT * 0.83 - 50));
  m_PlayerTwoIcon.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH * 0.55, Game::WINDOW_HEIGHT * 0.83 - 50));

  addDrawable(&m_PlayerOneText);
  addDrawable(&m_PlayerTwoText);

  addDrawable(&m_PlayerOneIcon);
  addDrawable(&m_PlayerTwoIcon);

  addUI(&m_SaveButton);
  addUI(&m_QuitButton);
  addUI(&m_UndoButton);

  if (!m_IconShader.loadFromFile("assets/shaders/PlayerIcon.frag",
                                 sf::Shader::Fragment)) {
    std::cerr << "Could not load PlayerIcon fragment shader!" << std::endl;
  }
}
GameScene::GameScene(const std::string& savegame) : GameScene() {
  std::cout << "GameScene Load Save " << savegame << std::endl;
  m_SaveGame->LoadFromSave(savegame);
  UpdateTextAndIcons(true);
}

void GameScene::UpdateTextAndIcons(bool force_update) {
  // Change texture of icon if turns differ
  if (force_update || m_PrevTurn != m_GameBoard->GetCurrPlayer()->occupation) {
    m_PrevTurn = m_GameBoard->GetCurrPlayer()->occupation;
    // Change texture of the Turn icon
    m_TurnIcon.setTexture(m_PrevTurn == Token::Occupation::PEPE
                              ? m_PlayerOneTexture
                              : m_PlayerTwoTexture);
  }
  // Set the turn string
  std::string turn{m_PrevTurn == Token::Occupation::PEPE ? "Pepe - "
                                                         : "Doge - "};
  switch (m_GameBoard->GetState()) {
    case GameBoard::PLACE:
      turn += "Place";
      break;
    case GameBoard::CAPTURE:
      turn += "Capture";
      break;
    case GameBoard::MOVE:
      turn += "Move";
      break;
  }
  m_TurnText.setString(turn);
}

void GameScene::Update(sf::Event event) {
  Scene::Update(event);
  if (m_IsKilled) {
    Game::GetInstance().PopScene();
    return;
  }
  m_GameBoard->Update(event);
  UpdateTextAndIcons();
}

void GameScene::Render(sf::RenderWindow& window) {
  Scene::Render(window);
  m_IconShader.setUniform("elapsedTime",
                          (float)localClock.getElapsedTime().asMilliseconds());
  m_IconShader.setUniform("texture", sf::Shader::CurrentTexture);
  window.draw(m_TurnIcon, &m_IconShader);
  window.draw(m_TurnText, &m_IconShader);
  m_GameBoard->Render(window);
}
