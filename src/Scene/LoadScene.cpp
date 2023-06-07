#include "LoadScene.hpp"

#include <filesystem>
#include <string>

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "GameScene.hpp"

void LoadScene::Update(sf::Event event) {
  Scene::Update(event);
  if (m_IsKilled) {
    Game::GetInstance().PopScene();
    return;
  }
}

void LoadScene::Render(sf::RenderWindow& window) { Scene::Render(window); }

#include <iostream>
LoadScene::LoadScene()
    : m_MenuButton{"Menu", [&](sf::Event e) { m_IsKilled = true; }},
      m_IsKilled{false} {
  auto width = Game::WINDOW_WIDTH;
  auto height = Game::WINDOW_HEIGHT;
  AssetManager& assMan = AssetManager::GetInstance();

  auto btnTexture = assMan.GetTexture(GameAsset::BUTTON_NEWGAME).get();
  m_MenuButton.setTexture(btnTexture);

  m_MenuButton.setPosition(sf::Vector2f(width * 0.05, height * 0.9));
  addUI(&m_MenuButton);

  // Save slot buttons
  for (int i = 0; i < Game::SAVE_NUM; i++) {
    std::string filename = "./save/save" + std::to_string(i) + ".txt";
    std::string buttonText = "";
    // Try opening file
    if (!std::filesystem::exists(filename)) {
      buttonText = "Empty";
    } else {
      buttonText = "Savegame #" + std::to_string(i);
    }
    m_LoadButtons.push_back(std::make_unique<graphics::Button>(
        buttonText, [buttonText, filename](sf::Event e) {
          std::cout << "Button Text: " << buttonText << std::endl;
          std::cout << "Filename: " << filename << std::endl;
          if (buttonText != "Empty") {
            Game::GetInstance().PushScene(
                std::make_unique<GameScene>(filename));
          }
        }));
    m_LoadButtons.back()->setPosition(
        sf::Vector2f(width * 0.5 - m_LoadButtons.back()->getSize().x / 2 + 15.,
                     height * 0.35 + i * 75));
    m_LoadButtons.back()->setTexture(btnTexture);
    addUI(m_LoadButtons.back().get());
  }

  // Title and title background
  const auto textColor = sf::Color(0xE6, 0xE0, 0xE9);
  m_TitleText.setString("Load Game");
  m_TitleText.setCharacterSize(32);
  m_TitleText.setFillColor(textColor);
  m_TitleText.setFont(*assMan.GetFont(GameAsset::Font::COMFORTAA));
  m_TitleText.setPosition(sf::Vector2f(
      width * 0.5 - m_TitleText.getLocalBounds().width / 2, height * 0.15));
  m_TitleBackground.setFillColor(sf::Color(0x21, 0x1f, 0x26));
  m_TitleBackground.setSize(
      sf::Vector2f(m_TitleText.getLocalBounds().width * (1 + 2 / 3.f),
                   m_TitleText.getLocalBounds().height * 4));
  m_TitleBackground.setPosition(sf::Vector2f(
      width * 0.5 - m_TitleText.getLocalBounds().width * (0.5 + 1 / 3.f),
      height * 0.15 - m_TitleText.getLocalBounds().height));

  addDrawable(&m_TitleBackground);
  addDrawable(&m_TitleText);
}
LoadScene::~LoadScene() {}
