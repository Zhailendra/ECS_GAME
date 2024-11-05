/*
** PROJECT, 2024
** CPP_POOL
** File description:
** HitboxSystem.hpp
*/

#pragma once

#include <iostream>

#include "ASystem.hpp"
#include "Renderable/RenderableComponent.hpp"
#include "Controllable/ControllableComponent.hpp"
#include "Velocity/VelocityComponent.hpp"
#include "Position/PositionComponent.hpp"
#include "Walls/WallsComponent.hpp"
#include "Pellets/PelletsComponent.hpp"
#include "Energizers/EnergizersComponent.hpp"
#include "Door/DoorComponent.hpp"
#include "Map.hpp"
#include "EntityManager.hpp"

namespace game {

    class HitboxSystem : public ASystem {
        public:
            HitboxSystem();
            ~HitboxSystem();

            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() final;
            void addEntity(std::shared_ptr<Entity> &entity) final;
            void update(int gameLevel, bool resetGame) final;

            void checkPlayerHitbox(const std::shared_ptr<Entity> &entity, int gameLevel);
            void checker(int x, int y, bool &isWall, bool isPellet, bool useDoor);
            void checkIfPlayerHitGhost(double x, double y, ControllableComponent &player);

            bool verifyNextPos(double x, double y, bool isPellet, bool useDoor);

        protected:
        private:
    };

}