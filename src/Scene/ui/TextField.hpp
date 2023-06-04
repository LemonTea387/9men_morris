#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <string>

class TextField : public sf::Transformable, public sf::Drawable {
 public:
  TextField();
  ~TextField();
  void handleInput(sf::Event e);

 private:
  unsigned int m_size;
  std::string m_text;
  sf::RectangleShape m_rect;
  bool m_hasfocus;
  const std::string& getText() const;
  void setPosition(float x, float y);
  bool contains(sf::Vector2f point) const;
  void setFocus(bool focus);
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};