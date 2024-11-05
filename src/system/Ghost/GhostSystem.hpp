/*
** PROJECT, 2024
** CPP_POOL
** File description:
** GhostSystem.hpp
*/

#pragma once

#include <iostream>

#include "ASystem.hpp"
#include "Ghost/GhostComponent.hpp"
#include "Velocity/VelocityComponent.hpp"
#include "Rectable/RectableComponent.hpp"
#include "Position/PositionComponent.hpp"
#include "Renderable/RenderableComponent.hpp"
#include "Controllable/ControllableComponent.hpp"

namespace game {

    class GhostSystem : public ASystem {
        public:
            GhostSystem();
            ~GhostSystem() override = default;

            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() final;
            void addEntity(std::shared_ptr<Entity> &entity) final;
            void update(int gameLevel, bool resetGame) final;

            void setDirection(VelocityComponent &velocity, GhostComponent &ghost, PositionComponent &pos, int &optimal_direction, int &available_ways);
            void slowGhost(GhostComponent &ghost, VelocityComponent &velocity, RectableComponent &rect, int &optimal_direction, int &available_ways);
            static double findTarget(int direction, GhostComponent &ghost, PositionComponent &pos);

            void findPlayer(GhostComponent &ghost, PositionComponent &pos, PositionComponent &playerPosition, int playerDirection);
            static void sendToCorners(GhostComponent &ghost);
            void chaseMode(GhostComponent &ghost, PositionComponent &position, PositionComponent &playerPosition, int playerDirection);
            void manageFrightenedMode(GhostComponent &ghost, PositionComponent &pos, VelocityComponent &vel, int energizerTimer, int gameLevel, int &speed);
            void changeDisplay(GhostComponent &ghost, RenderableComponent &render, RectableComponent &rect, int energizerTimer);

            void reset(int gameLevel);

        protected:
        private:
    };

}