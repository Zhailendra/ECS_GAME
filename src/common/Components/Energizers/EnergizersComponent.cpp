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
    }

    EnergizersComponent::~EnergizersComponent()
    {
    }

    int EnergizersComponent::getNbEnergizersEaten() const {
        return _nbEnergizersEaten;
    }

    void EnergizersComponent::setNbEnergizersEaten(bool isEaten) {
        if (isEaten)
            _nbEnergizersEaten++;
    }

}
