/*
** PROJECT, 2024
** CPP_POOL
** File description:
** GhostComponent.cpp
*/

#include "GhostComponent.hpp"

namespace game {

    GhostComponent::GhostComponent() {
        _type = Components::GHOSTS;
        _animationTimer = 0;
        _direction = 0;
    }

    GhostComponent::GhostComponent(int ghostId) {
        _type = Components::GHOSTS;
        _ghostId = ghostId;
        _animationTimer = 0;
        _direction = 0;
    }

}
