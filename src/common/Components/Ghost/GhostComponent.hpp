/*
** PROJECT, 2024
** CPP_POOL
** File description:
** GhostComponent.hpp
*/

#pragma once

#include <iostream>

#include "AComponent.hpp"

constexpr int GHOST_ANIMATION_SPEED = 4;
constexpr int GHOST_ANIMATION_FRAMES = 6;


namespace game {

    class GhostComponent : public AComponent {
        public:
            GhostComponent();
            GhostComponent(int ghostId);
            ~GhostComponent() override = default;

            int getGhostId() const { return _ghostId; }
            int getAnimationTimer() const { return _animationTimer; }
            int getDirection() const { return _direction; }

            void setAnimationTimer(int animationTimer) { _animationTimer = animationTimer; }

        protected:
        private:
            int _ghostId;
            int _animationTimer;
            int _direction;
    };

}