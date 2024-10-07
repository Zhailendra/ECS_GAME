/*
** PROJECT, 2024
** CPP_POOL
** File description:
** PositionComponent.cpp
*/

#include "PositionComponent.hpp"

namespace game {

    PositionComponent::PositionComponent(double x, double y) : x(x), y(y)
    {
        _type = Components::POSITION;
    }

    void PositionComponent::setPos(double x, double y)
    {
        this->x = x;
        this->y = y;

        if (positionChangeCallback) {
            positionChangeCallback(x, y);
        }
    }

    void PositionComponent::positionCallback(std::function<void(float, float)> callback) {
        positionChangeCallback = std::move(callback);
    }

    bool PositionComponent::operator==(const PositionComponent &rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }

    pos PositionComponent::getPos() const {
        return {x, y};
    }
}
