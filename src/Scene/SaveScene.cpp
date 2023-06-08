#include "SaveScene.hpp"

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "../SaveGame.hpp"

void SaveScene::Update(sf::Event event) {
  Scene::Update(event);
  if (m_IsKilled) {
    Game::GetInstance().PopScene();
    return;
  }
}

void SaveScene::Render(sf::RenderWindow& window) { Scene::Render(window); }

SaveScene::SaveScene(SaveGame* savegame)
    : m_BackButton{"Back", [&](sf::Event e) { m_IsKilled = true; }},
      m_IsKilled{false},
      m_SaveGame(savegame) {
  auto width = Game::WINDOW_WIDTH;
  auto height = Game::WINDOW_HEIGHT;

  AssetManager& assMan = AssetManager::GetInstance();

  auto btnTexture = assMan.GetTexture(GameAsset::BUTTON_NEWGAME).get();
  m_BackButton.setTexture(btnTexture);

  m_BackButton.setPosition(sf::Vector2f(width * 0.05, height * 0.9));

  addUI(&m_BackButton);

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
    m_SaveButtons.push_back(std::make_unique<graphics::Button>(
        buttonText, [buttonText, filename, this](sf::Event e) {
          this->m_SaveGame->SaveGameFile(filename);
          this->m_IsKilled = true;
        }));
    m_SaveButtons.back()->setPosition(
        sf::Vector2f(width * 0.5 - m_SaveButtons.back()->getSize().x / 2 + 15.,
                     height * 0.35 + i * 75));
    m_SaveButtons.back()->setTexture(btnTexture);
    addUI(m_SaveButtons.back().get());
  }

  // Title and title background
  const auto textColor = sf::Color(0xE6, 0xE0, 0xE9);
  m_TitleText.setString("Save Game");
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
SaveScene::~SaveScene() {}
