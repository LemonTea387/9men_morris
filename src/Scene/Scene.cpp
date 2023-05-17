#include "Scene.hpp"

void Scene::Update(sf::Event event) {}
void Scene::Render(sf::RenderWindow& window) {}

void Scene::addUI(graphics::UI* ui) { m_ui.emplace_back(ui); }
void Scene::addDrawable(sf::Drawable* drawable) {
  m_draw.emplace_back(drawable);
}

Scene::Scene() {}
Scene::~Scene() {}
