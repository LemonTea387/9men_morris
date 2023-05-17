#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>

#include "ui/UI.hpp"
class Scene {
 public:
  virtual void Update(sf::Event event);
  virtual void Render(sf::RenderWindow& window);
  void addUI(graphics::UI* ui);
  void addDrawable(sf::Drawable* drawable);
  Scene();
  virtual ~Scene();

 protected:
  std::vector<graphics::UI*> m_ui{};
  std::vector<sf::Drawable*> m_draw{};
};

#endif
