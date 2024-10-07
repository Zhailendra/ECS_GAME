/*
** PROJECT, 2024
** CPP_POOL
** File description:
** PositionComponent.hpp
*/

#pragma once

#include <iostream>
#include <functional>
#include "AComponent.hpp"
#include "Includes.hpp"

namespace game {
    class PositionComponent : public AComponent {
        public:
            explicit PositionComponent(double x = 0, double y = 0);
            ~PositionComponent() override = default;

            void setPos(double x, double y);

            pos getPos() const;

            void positionCallback(std::function<void(float, float)> callback);

            bool operator==(const PositionComponent &rhs) const;

            double x;
            double y;
        private:
            std::function<void(double, double)> positionChangeCallback;
    };
};
