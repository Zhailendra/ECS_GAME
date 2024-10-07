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

            int getNbEnergizersEaten() const;

            void setNbEnergizersEaten(bool isEaten);

        protected:
        private:
            int _nbEnergizersEaten;
    };

}