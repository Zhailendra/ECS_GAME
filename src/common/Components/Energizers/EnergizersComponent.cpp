/*
** PROJECT, 2024
** CPP_POOL
** File description:
** EnergizersComponent.cpp
*/

#include "EnergizersComponent.hpp"

namespace game {

    EnergizersComponent::EnergizersComponent()
    {
        _type = Components::ENERGIZERS;
        _isEaten = false;
        _alreadyConsumed = false;
    }

    EnergizersComponent::~EnergizersComponent()
    {
    }

}
