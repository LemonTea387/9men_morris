#include "Game.hpp"

#include "Scene/MenuScene.hpp"
#include "Scene/Scene.hpp"

Game::Game() {}
Game::~Game() {}

void Game::PopScene() { m_Scenes.pop_back(); }
void Game::PushScene(ScenePtr&& scene) { m_Scenes.push_back(std::move(scene)); }

void Game::Loop() const {
  sf::Event event;
  while (Game::GetWindow().pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      Game::GetWindow().close();
    }
    m_Scenes.back()->Update();
  }

  Game::GetWindow().clear();
  m_Scenes.back()->Render();
  Game::GetWindow().display();
}

void Game::Run() {
  // Do Future Set Up Work here
  // (Initialise Logging or whatever)
  //

  // Set first Scene
  // Use emplace_back instead of push_back
  // because this way I don't have to convert
  // the argument to a unique_ptr myself.
  m_Scenes.emplace_back(new MenuScene());

  while (m_Scenes.size() > 0 && Game::GetWindow().isOpen()) {
    this->Loop();
  }

  Loop();
}
