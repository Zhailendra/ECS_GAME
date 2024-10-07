/*
** PROJECT, 2024
** CPP_POOL
** File description:
** VelocityComponent.cpp
*/

#include "VelocityComponent.hpp"

namespace game {

    VelocityComponent::VelocityComponent(float x, float y) : x(x), y(y)
    {
        _type = Components::VELOCITY;
    }

}
