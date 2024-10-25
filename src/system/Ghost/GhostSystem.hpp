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

namespace game {

    class GhostSystem : public ASystem {
        public:
            GhostSystem();
            ~GhostSystem() override = default;

            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() final;
            void addEntity(std::shared_ptr<Entity> &entity) final;
            void update() final;

        protected:
        private:
            int _direction;
    };

}