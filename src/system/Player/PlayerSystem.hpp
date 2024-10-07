/*
** PROJECT, 2024
** CPP_POOL
** File description:
** PlayerSystem.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "ASystem.hpp"
#include "Controllable/ControllableComponent.hpp"
#include "Velocity/VelocityComponent.hpp"
#include "Rectable/RectableComponent.hpp"
#include "Position/PositionComponent.hpp"
#include "Renderable/RenderableComponent.hpp"
#include "Includes.hpp"

namespace game {

    class PlayerSystem : public ASystem {
        public:
            PlayerSystem();
            ~PlayerSystem() override;

            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() final;
            void addEntity(std::shared_ptr<Entity> &entity) final {};

            void setDirection(ControllableComponent &controllable);

            int getNbPellets() const;

            void update() final;

        protected:
        private:
            int _animTime;
            int _nbPellets;
            int _direction;
    };

}