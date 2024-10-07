/*
** PROJECT, 2024
** CPP_POOL
** File description:
** AComponent.cpp
*/

#include "AComponent.hpp"

namespace game {

    AComponent::AComponent() {
    }

    Components AComponent::getType() const
    {
        return _type;
    }

    void AComponent::setType(Components type)
    {
        _type = type;
    }

}
