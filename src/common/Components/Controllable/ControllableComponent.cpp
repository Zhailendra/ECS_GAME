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
        this->_canMove = 0;
        this->_direction = 0;
        this->_lastDirection = 0;
        this->up = up;
        this->down = down;
        this->left = left;
        this->right = right;
    }

    ControllableComponent::~ControllableComponent()
    {
    }

    void ControllableComponent::setDirection(int direction) {
        this->_direction = direction;
    }

    void ControllableComponent::setLastDirection(int direction) {
        this->_lastDirection = direction;
    }

    void ControllableComponent::setCanMove(int canMove) {
        this->_canMove = canMove;
    }

    void ControllableComponent::setIsWall(std::array<bool, 4> isWall) {
        this->_isWall = isWall;
    }

    int ControllableComponent::getDirection() const {
        return this->_direction;
    }

    int ControllableComponent::getLastDirection() const {
        return this->_lastDirection;
    }

    int ControllableComponent::getCanMove() const {
        return this->_canMove;
    }

    std::array<bool, 4> ControllableComponent::getIsWall() const {
        return this->_isWall;
    }

}
