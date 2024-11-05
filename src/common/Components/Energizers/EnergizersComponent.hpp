/*
** PROJECT, 2024
** CPP_POOL
** File description:
** EnergizersComponent.hpp
*/

#pragma once

#include <iostream>

#include "AComponent.hpp"
#include "Types.hpp"

namespace game {

    class EnergizersComponent : public AComponent {
        public:
            EnergizersComponent();
            ~EnergizersComponent();

            bool getIsEaten() const { return _isEaten; }
            void setIsEaten(bool eaten) { _isEaten = eaten; }

            bool isAlreadyConsumed() const { return _alreadyConsumed; }
            void setAlreadyConsumed(bool consumed) { _alreadyConsumed = consumed; }

        private:
            bool _isEaten;
            bool _alreadyConsumed;
    };

}