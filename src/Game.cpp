#include "Game.hpp"

#include "Scene/MenuScene.hpp"
#include "Scene/Scene.hpp"

Game::Game() {}
Game::~Game() {}

void Game::PopScene() { m_Scenes.pop_back(); }
void Game::PushScene(ScenePtr&& scene) { m_Scenes.push_back(std::move(scene)); }

void Game::Loop() const {
  m_Scenes.back()->Update();
  m_Scenes.back()->Render();
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

  while (m_Scenes.size() > 0) {
    this->Loop();
  }

  Loop();
}
