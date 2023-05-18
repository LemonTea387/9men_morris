#include "Scene.hpp"

void Scene::Update(sf::Event event) {
  if (event.type == sf::Event::MouseButtonReleased) {
    for (auto& e : m_ui) {
      e->notifyListeners(event);
    }
  }
}
void Scene::Render(sf::RenderWindow& window) {
  for (auto& e : m_ui) {
    window.draw(*e);
  }

  for (auto& e : m_draw) {
    window.draw(*e);
  }
}

void Scene::addUI(graphics::UI* ui) { m_ui.emplace_back(ui); }
void Scene::addDrawable(sf::Drawable* drawable) {
  m_draw.emplace_back(drawable);
}

Scene::Scene() {}
Scene::~Scene() {}
