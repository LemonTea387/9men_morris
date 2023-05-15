#ifndef WINSCENE_H
#define WINSCENE_H
#include "Scene.hpp"
#include "ui/Button.hpp"

enum PlayerType { DOGE, PEPE };

class WinScene : public Scene {
 private:
  graphics::Button m_PlaceholderButton;

 public:
  WinScene(PlayerType);
  ~WinScene();
  virtual void Update(sf::Event event) override;
  virtual void Render() override;
};

#endif
