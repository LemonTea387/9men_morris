#include "GameScene.hpp"

#include <iostream>

#include "../Game.hpp"
#include "../Tile.hpp"

GameScene::GameScene()
    : m_SaveButton{"Save",
                   [&](sf::Event e) { m_SaveButton.setText("Test Save"); }},
      m_QuitButton{"Quit",
                   [&](sf::Event e) { m_QuitButton.setText("Test Quit"); }} {
  if (!m_ButtonFont.loadFromFile(
          "assets/fonts/Comfortaa/static/Comfortaa-SemiBold.ttf")) {
    std::cerr << "Could not load font!" << std::endl;
  }
  if (!m_ButtonTexture.loadFromFile("assets/ui/buttons/Exit.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }

  m_SaveButton.setFont(m_ButtonFont);
  m_SaveButton.setTexture(m_ButtonTexture);
  m_SaveButton.setPosition(sf::Vector2f(799.f, 916.f));

  m_QuitButton.setFont(m_ButtonFont);
  m_QuitButton.setTexture(m_ButtonTexture);
  m_QuitButton.setPosition(sf::Vector2f(51.f, 909.f));

  m_PlayerOneText.setFont(m_ButtonFont);
  m_PlayerOneText.setString("Player 1");
  m_PlayerOneText.setCharacterSize(32);
  m_PlayerOneText.setPosition(sf::Vector2f(332.f, 815.f));

  m_PlayerTwoText.setFont(m_ButtonFont);
  m_PlayerTwoText.setString("Player 2");
  m_PlayerTwoText.setCharacterSize(32);
  m_PlayerTwoText.setPosition(sf::Vector2f(687.f, 815.f));

  m_TurnText.setFont(m_ButtonFont);
  m_TurnText.setString("Player 2 Move Token");
  m_TurnText.setCharacterSize(48);
  m_TurnText.setPosition(sf::Vector2f(313.f, 42.f));

  addDrawable(&m_PlayerOneText);
  addDrawable(&m_PlayerTwoText);
  addDrawable(&m_TurnText);

  if (!m_PlayerOneTexture.loadFromFile("assets/ui/buttons/Pepe.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }

  if (!m_PlayerTwoTexture.loadFromFile("assets/ui/buttons/Doge.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }

  if (!m_TurnTexture.loadFromFile("assets/ui/buttons/Doge.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }

  m_PlayerOneIcon.setSize(sf::Vector2f(90, 90));
  m_PlayerTwoIcon.setSize(sf::Vector2f(90, 90));
  m_TurnIcon.setSize(sf::Vector2f(115, 115));

  m_PlayerOneIcon.setTexture(&m_PlayerOneTexture);
  m_PlayerTwoIcon.setTexture(&m_PlayerTwoTexture);
  m_TurnIcon.setTexture(&m_TurnTexture);

  m_PlayerOneIcon.setPosition(sf::Vector2f(213, 790));
  m_PlayerTwoIcon.setPosition(sf::Vector2f(567, 790));
  m_TurnIcon.setPosition(sf::Vector2f(157, 15));

  addDrawable(&m_PlayerOneIcon);
  addDrawable(&m_PlayerTwoIcon);
  addDrawable(&m_TurnIcon);

  addUI(&m_SaveButton);
  addUI(&m_QuitButton);  
  for (const auto& outer : m_GameBoard.horizontal_board) {
    for (const auto& inner : outer) {
      addUI(inner.get());
    }
  }
}

void GameScene::Update(sf::Event event) {
  m_GameBoard.Update(event);
  if (event.type == sf::Event::MouseButtonReleased) {
    for (auto& e : m_ui) {
      e->notifyListeners(event);
    }
  }
}

void GameScene::Render() {
  sf::RenderWindow& window = Game::GetWindow();

  for (auto& e : m_ui) {
    window.draw(*e);
  }

  for (auto& e : m_draw) {
    window.draw(*e);
  }

  // TODO Abstract gameboard to its own
  // GameBoard drawing
  m_GameBoard.Render();
}
