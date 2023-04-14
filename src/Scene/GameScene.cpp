#include "GameScene.hpp"

#include <iostream>

#include "../Game.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

GameScene::GameScene()
    : m_Board(sf::Vector2f(509.f, 542.f)), m_BoardPos(184.f, 171.f) {
  m_Board.setPosition(m_BoardPos);
  if (!m_BoardTexture.loadFromFile("assets/ui/Board.png")) {
    std::cerr << "Could not load Board Texture!" << std::endl;
  }
  m_Board.setTexture(&m_BoardTexture);
}

GameScene::~GameScene() {}

void GameScene::Update(sf::Event event) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Left) {
      m_BoardPos.x -= 1.0f;
    } else if (event.key.code == sf::Keyboard::Right) {
      m_BoardPos.x += 1.0f;
    }
    if (event.key.code == sf::Keyboard::Up) {
      m_BoardPos.y -= 1.0f;
    } else if (event.key.code == sf::Keyboard::Down) {
      m_BoardPos.y += 1.0f;
    }
    m_Board.setPosition(m_BoardPos);
  }

  if (event.type == sf::Event::KeyReleased &&
      event.key.code == sf::Keyboard::X) {
    std::cout << "(" << m_BoardPos.x << ", " << m_BoardPos.y << ")"
              << std::endl;
  }
}

void GameScene::Render() { Game::GetWindow().draw(m_Board); }
