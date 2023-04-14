#include "GameScene.hpp"

#include <iostream>

#include "../Game.hpp"

GameScene::GameScene() : m_Board(sf::Vector2f(509.f, 542.f)) {
  m_Board.setPosition(sf::Vector2f(184.f, 171.f));
  if (!m_BoardTexture.loadFromFile("assets/ui/Board.png")) {
    std::cerr << "Could not load Board Texture!" << std::endl;
  }
  m_Board.setTexture(&m_BoardTexture);
}

GameScene::~GameScene() {}

void GameScene::Update(sf::Event event) {}

void GameScene::Render() { Game::GetWindow().draw(m_Board); }
