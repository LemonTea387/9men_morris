#include "Game.hpp"

#include <SFML/Audio.hpp>

#include "Scene/MenuScene.hpp"
#include "Scene/Scene.hpp"
Game::Game() { Game::GetWindow().setFramerateLimit(30); }
Game::~Game() {}

void Game::PopScene() { m_Scenes.pop_back(); }
void Game::PushScene(ScenePtr&& scene) { m_Scenes.push_back(std::move(scene)); }

void Game::Loop() {
  sf::Event event;
  while (Game::GetWindow().pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_Scenes.clear();
    }
    if (m_Scenes.size() > 0) {
      m_Scenes.back()->Update(event);
    }
  }

  if (m_Scenes.size() > 0) {
    Game::GetWindow().clear();
    Game::GetWindow().draw(m_BackgroundColor);
    if (m_Scenes.size() > 0) {
      m_Scenes.back()->Render(Game::GetWindow());
    }
    Game::GetWindow().display();
  }
}

void Game::Run() {
  // Do Future Set Up Work here
  // (Initialise Logging or whatever)
  //
  if (m_BackgroundMusic.openFromFile("assets/sounds/background.ogg")) {
    m_BackgroundMusic.setLoop(true);
    m_BackgroundMusic.play();
  }

  m_BackgroundColor.setFillColor(sf::Color(0x14, 0x12, 0x18));
  m_BackgroundColor.setPosition(sf::Vector2f(0.f, 0.f));
  m_BackgroundColor.setSize(
      sf::Vector2f(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));

  // Set first Scene
  m_Scenes.emplace_back(std::make_unique<MenuScene>());

  while (m_Scenes.size() > 0 && Game::GetWindow().isOpen()) {
    this->Loop();
  }

  if (Game::GetWindow().isOpen()) {
    Game::GetWindow().close();
  }
}
