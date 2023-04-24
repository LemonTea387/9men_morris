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
  m_SaveButton.setPosition(sf::Vector2f(695.f, 803.f));

  m_QuitButton.setFont(m_ButtonFont);
  m_QuitButton.setTexture(m_ButtonTexture);
  m_QuitButton.setPosition(sf::Vector2f(40.f, 803.f));

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

  // TODO Abstract gameboard to its own
  // GameBoard drawing
  m_GameBoard.Render();
}
