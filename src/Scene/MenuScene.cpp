#include "MenuScene.hpp"

#include <iostream>

#include "../Game.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
void MenuScene::Update(sf::Event event) {
  if (event.type == sf::Event::MouseButtonReleased &&
      event.mouseButton.button == sf::Mouse::Left) {
    if (m_ExitButton.getGlobalBounds().contains(event.mouseButton.x,
                                                event.mouseButton.y)) {
      Game::GetInstance().PopScene();
    }
  }
}

void MenuScene::Render(sf::RenderWindow& window) {
  window.draw(m_NewGameButton);
  window.draw(m_ConGameButton);
  window.draw(m_CreditsButton);
  window.draw(m_ExitButton);

  window.draw(m_NewGameText);
  window.draw(m_ConGameText);
  window.draw(m_CreditsText);
  window.draw(m_ExitText);

  window.draw(m_DogeVsPepe);
}

MenuScene::MenuScene()
    : m_NewGameButton(sf::Vector2f(261.f, 66.f)),
      m_ConGameButton(sf::Vector2f(356.f, 74.f)),
      m_CreditsButton(sf::Vector2f(206.f, 74.f)),
      m_ExitButton(sf::Vector2f(191.f, 73.f)),
      m_DogeVsPepe(sf::Vector2f(235.f, 115.f)) {
  m_NewGameButton.setPosition(319.f, 303.f);
  m_ConGameButton.setPosition(272.f, 395.f);
  m_CreditsButton.setPosition(347.f, 495.f);
  m_ExitButton.setPosition(354.f, 595.f);
  m_DogeVsPepe.setPosition(602.f, 728.f);

  m_NewGameText.setPosition(348.5f, 316.f);
  m_ConGameText.setPosition(312.5f, 405.f);
  m_CreditsText.setPosition(387.5f, 505.f);
  m_ExitText.setPosition(409.f, 610.f);
  if (!m_ButtonFont.loadFromFile(
          "assets/fonts/Comfortaa/static/Comfortaa-SemiBold.ttf")) {
    std::cerr << "Could not load font!" << std::endl;
  }
  if (!m_NewGameTexture.loadFromFile("assets/ui/buttons/NewGame.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }
  if (!m_ConGameTexture.loadFromFile("assets/ui/buttons/ConGame.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }
  if (!m_CreditsTexture.loadFromFile("assets/ui/buttons/Credits.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }
  if (!m_ExitTexture.loadFromFile("assets/ui/buttons/Exit.png")) {
    std::cerr << "Could not load UI button!" << std::endl;
  }
  if (!m_DogeVsPepeTexture.loadFromFile("assets/ui/buttons/DogeVsPepe.png")) {
    std::cerr << "Could not load DogeVsPepe!" << std::endl;
  }
  std::cerr << "Could not load DogeVsPepe!" << std::endl;
  m_NewGameButton.setTexture(&m_NewGameTexture);
  m_ConGameButton.setTexture(&m_ConGameTexture);
  m_CreditsButton.setTexture(&m_CreditsTexture);
  m_ExitButton.setTexture(&m_ExitTexture);
  m_DogeVsPepe.setTexture(&m_DogeVsPepeTexture);

  m_NewGameText.setFont(m_ButtonFont);
  m_NewGameText.setString("New Game");
  m_NewGameText.setCharacterSize(32);
  m_NewGameText.setFillColor(sf::Color(0xd0, 0xbc, 0xff));

  m_ConGameText.setFont(m_ButtonFont);
  m_ConGameText.setString("Continue Game");
  m_ConGameText.setCharacterSize(32);
  m_ConGameText.setFillColor(sf::Color(0xd0, 0xbc, 0xff));

  m_CreditsText.setFont(m_ButtonFont);
  m_CreditsText.setString("Credits");
  m_CreditsText.setCharacterSize(32);
  m_CreditsText.setFillColor(sf::Color(0xd0, 0xbc, 0xff));

  m_ExitText.setFont(m_ButtonFont);
  m_ExitText.setString("Quit");
  m_ExitText.setCharacterSize(32);
  m_ExitText.setFillColor(sf::Color(0xd0, 0xbc, 0xff));
}
MenuScene::~MenuScene() {}
