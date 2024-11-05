/*
** PROJECT, 2024
** CPP_POOL
** File description:
** PelletsComponent.cpp
*/

#include "PelletsComponent.hpp"

namespace game {

    PelletsComponent::PelletsComponent()
    {
        _type = Components::PELLETS;
        _isEaten = false;
        _alreadyConsumed = false;
    }

    PelletsComponent::~PelletsComponent()
    {
    }

}
