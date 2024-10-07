/*
** PROJECT, 2024
** CPP_POOL
** File description:
** VelocityComponent.hpp
*/

#pragma once

#include <iostream>
#include "AComponent.hpp"

namespace game {

    struct velocity {
        float x;
        float y;
    };

    class VelocityComponent : public AComponent {
        public:
            explicit VelocityComponent(float x = 0, float y = 0);
            ~VelocityComponent() override = default;

            float x;
            float y;
            float lastX;
            float lastY;
        private:
    };
};
