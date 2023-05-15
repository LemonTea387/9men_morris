#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "ui/UI.hpp"
class Scene{
 public:
  virtual void Update(sf::Event event) = 0;
  virtual void Update() = 0;
  virtual void Render(sf::RenderWindow& window) = 0;
  void addUI(graphics::UI* ui) { m_ui.emplace_back(ui); }
  void addDrawable(sf::Drawable* drawable) { m_draw.emplace_back(drawable); }

 protected:
  std::vector<graphics::UI*> m_ui{};
  std::vector<sf::Drawable*> m_draw{};
};

#endif
