#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SFML/Graphics.hpp>
#include <string>

#include "UI.hpp"
#include "OnClickEventListener.hpp"

namespace graphics {
class TextField : public UI {
 public:
  TextField(TextField const&) = delete;

  TextField(unsigned int size);

  virtual ~TextField();

  void HandleInput(sf::Event e);

  void Update(sf::Event e);

  void SetFocus(bool focus);

  const std::string& GetText() const;

  void setPosition(const sf::Vector2f& position);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

 private:
  typedef std::unique_ptr<OnClickEventListener> OCELPtr;
  unsigned int m_MaxSize;
  std::string m_Str;
  sf::RectangleShape m_Rect;
  sf::Text m_Text;
  bool m_HasFocus;
  OCELPtr m_ClickListener;
};
}  // namespace graphics
#endif
