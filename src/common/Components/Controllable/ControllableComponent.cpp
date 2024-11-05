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
        this->_isDead = false;
        this->up = up;
        this->down = down;
        this->left = left;
        this->right = right;
        this->_energyTimer = 0;
    }

    ControllableComponent::~ControllableComponent()
    {
    }

    void ControllableComponent::setIsPlaying(bool isPlaying) {
        this->_isPlaying = isPlaying;
    }

    void ControllableComponent::setIsDead(bool isDead) {
        this->_isDead = isDead;
    }

    void ControllableComponent::setEnergyTimer(int energyTimer) {
        this->_energyTimer = energyTimer;
    }

    bool ControllableComponent::getIsPlaying() const {
        return this->_isPlaying;
    }

    bool ControllableComponent::getIsDead() const {
        return this->_isDead;
    }

    int ControllableComponent::getEnergyTimer() const {
        return this->_energyTimer;
    }

}
