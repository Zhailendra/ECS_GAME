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
        _ghostId = 0;
        _animationTimer = 0;
        _direction = 0;
        _scatter = false;
        _useDoor = 0 < 0;
        _frightenedMode = NORMAL;
        _canMove = true;
    }

    GhostComponent::GhostComponent(int ghostId, pos bluePos, pos redPos) {
        _type = Components::GHOSTS;
        _ghostId = ghostId;
        _animationTimer = 0;
        _direction = 0;
        _scatter = false;
        _useDoor = 0 < ghostId;
        _frightenedMode = NORMAL;
        _homePosition = bluePos;
        _homeExitPosition = redPos;
        _targetPosition = redPos;
        _canMove = true;
    }

}
