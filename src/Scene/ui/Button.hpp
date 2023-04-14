#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SFML/Graphics.hpp>

/**
 * Button class as an abstraction of a compound UI with Rectangular button and Text. 
 * The Button is itself Drawable, a sf::RenderWindow can directly call draw on this 
 * compound UI. Position of the Button will be a base position of the compound UI
 * components.
 */
class Button : public sf::Drawable, public sf::Transformable{
    public:
        Button(Button const&) = delete;
        Button();
        Button(const sf::Texture& texture, const sf::Font& font, const std::string& buttonText);
        ~Button();

        /**
         * Setting all the position of the compound UI components to ensure everything
         * looks right.
         */
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