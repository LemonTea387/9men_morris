#include "CreditsScene.hpp"

#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"

namespace {
/**
 * Offset X to pad the X for displaying developers' names
 */
constexpr float CREDITS_X_OFFSET = Game::WINDOW_WIDTH / 5.f;
/**
 * Offset Y to pad the Y for displaying developers' names
 */
constexpr float CREDITS_Y_OFFSET = Game::WINDOW_HEIGHT / 6.f * 2.f;
/**
 * Padding in between each developers' names
 */
constexpr float CREDITS_VERT_SPACING = 100.f;
}  // namespace

void CreditsScene::Update(sf::Event event) { Scene::Update(event); }

void CreditsScene::Render(sf::RenderWindow& window) { Scene::Render(window); }

CreditsScene::CreditsScene()
    : m_ReturnButton{"Return",
                     [&](sf::Event e) { Game::GetInstance().PopScene(); }} {
  AssetManager& assMan = AssetManager::GetInstance();
  // Return to MainMenu Button
  m_ReturnButton.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH / 20.f, Game::WINDOW_HEIGHT / 7.f * 6.f));
  m_ReturnButton.setTexture(assMan.GetTexture(GameAsset::BUTTON_NEWGAME).get());

  addUI(&m_ReturnButton);

  // Title
  m_TitleBackground.setFillColor(sf::Color(0x21, 0x1f, 0x26));
  m_TitleBackground.setSize(sf::Vector2f(478.f, 94.f));
  m_TitleBackground.setPosition(
      sf::Vector2f(Game::WINDOW_WIDTH / 5.f, Game::WINDOW_HEIGHT / 7.f));
  addDrawable(&m_TitleBackground);

  const auto textColor = sf::Color(0xE6, 0xE0, 0xE9);

  m_TitleText.setString("Credits");
  m_TitleText.setCharacterSize(32);
  m_TitleText.setFillColor(textColor);
  m_TitleText.setFont(*assMan.GetFont(GameAsset::Font::COMFORTAA));
  m_TitleText.setPosition(sf::Vector2f(Game::WINDOW_WIDTH / 5.f + 170.f,
                                       Game::WINDOW_HEIGHT / 7.f + 30.f));
  addDrawable(&m_TitleText);

  // Developers
  m_Authors[0].setString("Chan Jia Zheng");
  m_Authors[1].setString("Low Jun Jie");
  m_Authors[2].setString("Naavin Ravinthran");

  // For calculating the spacings and hence where it is displayed along the Y
  int curAuthorIndex = 0;
  for (auto& author : m_Authors) {
    author.setCharacterSize(48);
    author.setFillColor(sf::Color(0xd0, 0xbc, 0xff));
    author.setFont(*assMan.GetFont(GameAsset::Font::ROBOTO_REGULAR));
    author.setPosition(sf::Vector2f(
        CREDITS_X_OFFSET,
        CREDITS_Y_OFFSET + (curAuthorIndex * CREDITS_VERT_SPACING)));
    curAuthorIndex++;
    addDrawable(&author);
  }
}
CreditsScene::~CreditsScene() {}
