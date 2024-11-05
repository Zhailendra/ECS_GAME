/*
** PROJECT, 2024
** CPP_POOL
** File description:
** TextComponent.hpp
*/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "AComponent.hpp"

namespace game {

    class TextComponent : public AComponent {
        public:
            TextComponent();
            TextComponent(const std::string &string, const sf::Color &color, unsigned int size, bool isGameOverText);
            ~TextComponent() = default;

            void setIsFontLoaded(bool isFontLoaded);
            void setStringText(const std::string &string);
            void setDisplay(bool display);
            void setDisplayNow(bool displayNow);

            bool getIsFontLoaded() const;
            std::string getString() const;
            sf::Text &getText();
            bool getDisplay() const;
            bool getDisplayNow() const;
            bool getIsGameOverText() const;

        protected:
            bool _isFontLoaded;
            bool _display;
            bool _displayNow;
            bool _isGameOverText;
        private:
            sf::Text _text;
            sf::Font _font;
            sf::Color _color;
            std::string _string;
    };

}