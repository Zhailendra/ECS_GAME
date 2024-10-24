/*
** PROJECT, 2024
** CPP_POOL
** File description:
** TextComponent.cpp
*/

#include "TextComponent.hpp"

namespace game {

    TextComponent::TextComponent() {
        _type = Components::TEXT;
    }

    TextComponent::TextComponent(const std::string &text, const sf::Color &color, unsigned int size) {
        _type = Components::TEXT;
        _text.setString(text);
        _string = text;
        _text.setFillColor(color);
        _text.setCharacterSize(size);
    }

    void TextComponent::setIsFontLoaded(bool isFontLoaded) {
        _isFontLoaded = isFontLoaded;
    }

    void TextComponent::setStringText(const std::string &string) {
        _string = string;
    }

    void TextComponent::setDisplay(bool display) {
        _display = display;
    }

    void TextComponent::setDisplayNow(bool displayNow) {
        _displayNow = displayNow;
    }

    sf::Text &TextComponent::getText() {
        return _text;
    }

    bool TextComponent::getIsFontLoaded() const {
        return _isFontLoaded;
    }

    std::string TextComponent::getString() const {
        return _string;
    }

    bool TextComponent::getDisplay() const {
        return _display;
    }

    bool TextComponent::getDisplayNow() const {
        return _displayNow;
    }

}
