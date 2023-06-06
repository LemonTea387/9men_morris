#include "TextField.hpp"

#include <memory>

#include "../../AssetManager.hpp"
#include "OnClickEventListener.hpp"

namespace graphics {
TextField::TextField(unsigned int size)
    : m_Rect{sf::Vector2f(15 * size, 20)},
      m_MaxSize{size},
      m_ClickListener{std::make_unique<OnClickEventListener>(
          this, [&](sf::Event e) { this->SetFocus(true); })} {
  AssetManager& assMan = AssetManager::GetInstance();
  m_Rect.setOutlineThickness(2);
  m_Rect.setFillColor(sf::Color::White);
  m_Rect.setOutlineColor(sf::Color(127, 127, 127));

  addEventListener(m_ClickListener.get());

  SetFocus(true);
}

TextField::~TextField() {}

const std::string& TextField::GetText() const { return m_Str; }

void TextField::setPosition(const sf::Vector2f& position) {
  sf::Transformable::setPosition(position);
  m_Rect.setPosition(position);
  m_Text.setPosition(sf::Vector2f(position.x + 10, position.y));
}

void TextField::SetFocus(bool focus) {
  m_HasFocus = focus;
  if (focus) {
    m_Rect.setOutlineColor(sf::Color::Blue);
  } else {
    m_Rect.setOutlineColor(sf::Color(127, 127, 127));  // Gray color
  }
}

void TextField::HandleInput(sf::Event e) {
  if (!m_HasFocus || e.type != sf::Event::TextEntered) return;

  if (e.text.unicode == 8) {  // Delete key
    m_Str = m_Str.substr(0, m_Str.size() - 1);
  } else if (m_Str.size() < m_MaxSize) {
    m_Str += e.text.unicode;
  }
}

void TextField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(m_Rect);
  target.draw(m_Text);
}
}  // namespace graphics
