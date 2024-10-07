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

            int getNbPelletsEaten() const;

            void setNbPelletsEaten(bool isEaten);

        protected:
        private:
            int _nbPelletsEaten;
    };

}