/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Movable.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ASystem.hpp"
#include "Position/PositionComponent.hpp"
#include "Velocity/VelocityComponent.hpp"
#include "Controllable/ControllableComponent.hpp"
#include "Walls/WallsComponent.hpp"
#include "Pellets/PelletsComponent.hpp"
#include "Energizers/EnergizersComponent.hpp"
#include "Door/DoorComponent.hpp"
#include "Ghost/GhostComponent.hpp"

namespace game {

    class MovableSystem : public ASystem {
        public:
            MovableSystem();
            ~MovableSystem();

            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() final;
            void addEntity(std::shared_ptr<Entity> &entity) final;
            void update() final;
        protected:
        private:
    };

}
