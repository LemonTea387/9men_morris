#include "GameScene.hpp"

#include <iostream>

#include "../Game.hpp"

GameScene::GameScene() : m_Board(sf::Vector2f(509.f, 542.f)) {
  m_Board.setPosition(sf::Vector2f(184.f, 171.f));
  if (!m_BoardTexture.loadFromFile("assets/ui/Board.png")) {
    std::cerr << "Could not load Board Texture!" << std::endl;
  }
  m_Board.setTexture(&m_BoardTexture);
  if (!m_ButtonFont.loadFromFile(
          "assets/fonts/Comfortaa/static/Comfortaa-SemiBold.ttf")) {
    std::cerr << "Could not load font!" << std::endl;
  }
  if (!m_ButtonTexture.loadFromFile("assets/ui/buttons/Exit.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }

  m_SaveButton = Button(m_ButtonTexture, m_ButtonFont, "Save");
  m_SaveButton.setPosition(sf::Vector2f(695.f, 803.f));
  m_QuitButton = Button(m_ButtonTexture, m_ButtonFont, "Quit");
  m_QuitButton.setPosition(sf::Vector2f(40.f, 803.f));
}

void GameScene::Update(sf::Event event) {}

void GameScene::Render() {
  sf::RenderWindow& window = Game::GetWindow();

  window.draw(m_SaveButton);
  window.draw(m_QuitButton);

  // TODO Abstract gameboard to its own
  // GameBoard drawing
  window.draw(m_Board);
}
