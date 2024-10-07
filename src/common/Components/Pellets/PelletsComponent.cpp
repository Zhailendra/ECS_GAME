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
        _nbPelletsEaten = 0;
    }

    PelletsComponent::~PelletsComponent()
    {
    }

    void PelletsComponent::setNbPelletsEaten(bool isEaten) {
        if (isEaten)
            _nbPelletsEaten++;
    }

    int PelletsComponent::getNbPelletsEaten() const {
        return _nbPelletsEaten;
    }

}
