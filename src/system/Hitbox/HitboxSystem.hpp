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

namespace game {

    class HitboxSystem : public ASystem {
        public:
            HitboxSystem();
            ~HitboxSystem();

            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() final;
            void addEntity(std::shared_ptr<Entity> &entity) final;
            void update() final;

            void checkPlayerHitbox(const std::shared_ptr<Entity> &entity);

            bool verifyNextPos(double x, double y, const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &map);

        protected:
        private:
    };

}