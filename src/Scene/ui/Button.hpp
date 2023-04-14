#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SFML/Graphics.hpp>

// Future abstracting of UI can be done here.
class Button : public sf::Drawable, public sf::Transformable{
    public:
        Button(Button const&) = delete;
        Button();
        Button(const sf::Texture& texture, const sf::Font& font, const std::string& buttonText);
        ~Button();
        void setPosition(const sf::Vector2f& position);
    private:
        static constexpr float MARGIN_X = 32.f;
        static constexpr float MARGIN_Y = 16.f;
        static constexpr int CHAR_SIZE = 32;
        sf::RectangleShape m_ButtonShape;
        sf::Text m_ButtonText;
        sf::Font m_ButtonFont;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif