/*
** PROJECT, 2024
** CPP_POOL
** File description:
** PelletsComponent.hpp
*/

#pragma once

#include <iostream>

#include "AComponent.hpp"
#include "Types.hpp"

namespace game {

    class PelletsComponent : public AComponent {
        public:
            PelletsComponent();
            ~PelletsComponent();

            bool getIsEaten() const { return _isEaten; }
            void setIsEaten(bool eaten) { _isEaten = eaten; }

            bool isAlreadyConsumed() const { return _alreadyConsumed; }
            void setAlreadyConsumed(bool consumed) { _alreadyConsumed = consumed; }

        private:
            bool _isEaten;
            bool _alreadyConsumed;
    };

}