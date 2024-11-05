/*
** PROJECT, 2024
** CPP_POOL
** File description:
** GameSystem.hpp
*/

#pragma once

#include <iostream>

#include "ASystem.hpp"
#include "Controllable/ControllableComponent.hpp"
#include "Ghost/GhostComponent.hpp"

namespace game {

    class GameSystem : public ASystem {
        public:
            GameSystem();
            ~GameSystem() override = default;

            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() final;
            void addEntity(std::shared_ptr<Entity> &entity) final;
            void update(int gameLevel, bool resetGame) final;

            void waveManager(int gameLevel);

            void reset(int gameLevel);

        protected:
            int _currentWave;
            int _waveTimer;
        private:
    };

}