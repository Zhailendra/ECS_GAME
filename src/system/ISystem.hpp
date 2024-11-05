/*
** PROJECT, 2024
** CPP_POOL
** File description:
** ISystem.hpp
*/

#pragma once

#include <iostream>

namespace game {
    class ISystem {
        public:
            ISystem();
            virtual ~ISystem() = 0;

            virtual void update(int gameLevel, bool resetGame) = 0;
        protected:
        private:
    };
}