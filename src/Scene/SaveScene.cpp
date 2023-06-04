#include "SaveScene.hpp"

#include "../Game.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"

void SaveScene::Update(sf::Event event) { Scene::Update(event); }

void SaveScene::Render(sf::RenderWindow& window) { Scene::Render(window); }

SaveScene::SaveScene()
    : m_SaveButton{"Save",
                     [&](sf::Event e) { Game::GetInstance().PopScene(); }},
      m_MenuButton{"Save", [&](sf::Event e) {
                     Game::GetInstance().PopScene();
                     Game::GetInstance().PopScene();
                   }} {

}
SaveScene::~SaveScene() {}