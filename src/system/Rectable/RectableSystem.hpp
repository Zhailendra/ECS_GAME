/*
** PROJECT, 2024
** CPP_POOL
** File description:
** RectableSystem.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ASystem.hpp"
#include "Rectable/RectableComponent.hpp"
#include "Renderable/RenderableComponent.hpp"
#include "Controllable/ControllableComponent.hpp"
#include "Walls/WallsComponent.hpp"
#include "Pellets/PelletsComponent.hpp"
#include "Energizers/EnergizersComponent.hpp"
#include "Door/DoorComponent.hpp"

namespace game {

    class RectableSystem : public ASystem {
        public:
            RectableSystem();
            ~RectableSystem();

            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() final;
            void addEntity(std::shared_ptr<Entity> &entity) final;
            void update() final;

        protected:
        private:
    };

}
