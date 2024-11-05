/*
** PROJECT, 2024
** CPP_POOL
** File description:
** RectableComponent.cpp
*/

#include "RectableComponent.hpp"

namespace game {

    RectableComponent::RectableComponent(int frameNumber) {
        _type = Components::RECTABLE;
        _currentPlayerFrame = frameNumber;
    }

    RectableComponent::RectableComponent(sf::IntRect rect) {
        _type = Components::RECTABLE;
        _rect = rect;
    }

    std::ostream &operator<<(std::ostream &os, const RectableComponent &rectable) {
        os << "RectableComponent{" << "keyHoldClock: " << rectable._keyHoldClock.getElapsedTime().asMilliseconds()
           << ", upKeyPressed: " << rectable._upKeyPressed
           << ", downKeyPressed: " << rectable._downKeyPressed
           << ", currentPlayerFrame: " << rectable._currentPlayerFrame
           << '}';
        return os;
    }

    void RectableComponent::setDirection(int direction) {
        _currentPlayerFrame = direction;
    }

    void RectableComponent::setFrameSpeed(float frameSpeed) {
        _animFrameSpeed = frameSpeed;
    }

    void RectableComponent::setRect(sf::IntRect rect) {
        _rect = rect;
    }

    int RectableComponent::getCurrentFrame() const {
        return _currentPlayerFrame;
    }

    float RectableComponent::getFrameSpeed() const {
        return _animFrameSpeed;
    }

    sf::IntRect RectableComponent::getRect() const {
        return _rect;
    }

}
