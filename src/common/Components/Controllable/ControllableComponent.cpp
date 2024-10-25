/*
** PROJECT, 2024
** CPP_POOL
** File description:
** ControllableComponent.cpp
*/

#include "ControllableComponent.hpp"

namespace game {

    ControllableComponent::ControllableComponent(sf::Keyboard::Key up, sf::Keyboard::Key down,
                                                 sf::Keyboard::Key left, sf::Keyboard::Key right)
    {
        _type = Components::CONTROLLABLE;
        this->_isPlaying = true;
        this->up = up;
        this->down = down;
        this->left = left;
        this->right = right;
    }

    ControllableComponent::~ControllableComponent()
    {
    }

    void ControllableComponent::setIsPlaying(bool isPlaying) {
        this->_isPlaying = isPlaying;
    }

    bool ControllableComponent::getIsPlaying() const {
        return this->_isPlaying;
    }

}
