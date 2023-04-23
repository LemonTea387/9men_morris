#ifndef SCENE_H
#define SCENE_H
#include "../GameObject.hpp"
#include "ui/UI.hpp"
class Scene : public GameObject {
 public:
  virtual void Update(sf::Event event) = 0;
  virtual void Render() = 0;
  void addUI(graphics::UI* ui) { m_ui.emplace_back(ui); }

 protected:
  std::vector<graphics::UI*> m_ui{};
};

#endif
