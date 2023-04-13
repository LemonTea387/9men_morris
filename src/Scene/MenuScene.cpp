#include "MenuScene.hpp"

#include <iostream>

#include "../Game.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
void MenuScene::Update(sf::Event event) {
  if (event.type == sf::Event::MouseButtonReleased &&
      event.mouseButton.button == sf::Mouse::Left) {
    if (m_QuitButton.getGlobalBounds().contains(event.mouseButton.x,
                                                event.mouseButton.y)) {
      Game::GetInstance().PopScene();
    }
  }
}

void MenuScene::Render() {
  sf::RenderWindow& window = Game::GetWindow();
  window.draw(m_QuitButton);
  window.draw(m_QuitText);
}

MenuScene::MenuScene()
    : m_QuitButton(sf::Vector2f(191.f, 73.f)),
      m_DogeVsPepe(sf::Vector2f(235.f, 115.f)) {
  m_QuitButton.setPosition(354.f, 595.f);
  m_QuitText.setPosition(409.f, 610.f);
  if (!m_ButtonFont.loadFromFile(
          "assets/fonts/Comfortaa/static/Comfortaa-SemiBold.ttf")) {
    std::cerr << "Could not load font!" << std::endl;
  }
  if (!m_QuitTexture.loadFromFile("assets/ui/buttons/Exit.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }
  m_QuitButton.setTexture(&m_QuitTexture);
  m_QuitText.setFont(m_ButtonFont);
  m_QuitText.setString("Quit");
  m_QuitText.setCharacterSize(32);
  m_QuitText.setFillColor(sf::Color(0xd0, 0xbc, 0xff));
}
MenuScene::~MenuScene() {}
