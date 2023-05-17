#include "Game.hpp"

#include "Scene/GameScene.hpp"
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

  m_BackgroundColor.setFillColor(sf::Color(0x14, 0x12, 0x18));
  m_BackgroundColor.setPosition(sf::Vector2f(0.f, 0.f));
  m_BackgroundColor.setSize(
      sf::Vector2f(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));

  // Set first Scene
  // Use emplace_back instead of push_back
  // because this way I don't have to convert
  // the argument to a unique_ptr myself.
  // Temporarily set to GameScene first because I'm too lazy to add the button
  // to the MenuScene
  m_Scenes.emplace_back(new GameScene());

  while (m_Scenes.size() > 0 && Game::GetWindow().isOpen()) {
    this->Loop();
  }

  if (Game::GetWindow().isOpen()) {
    Game::GetWindow().close();
  }
}
