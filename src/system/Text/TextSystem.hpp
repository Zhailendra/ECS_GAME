/*
** PROJECT, 2024
** CPP_POOL
** File description:
** TextSystem.hpp
*/

#pragma once

#include <iostream>

#include "ASystem.hpp"
#include "Text/TextComponent.hpp"
#include "Position/PositionComponent.hpp"
#include "Path.hpp"

namespace game {

    class TextSystem : public ASystem {
        public:
            TextSystem();
            ~TextSystem() override = default;

            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() override;
            void addEntity(std::shared_ptr<Entity> &entity) final;
            void update() final;

        protected:
        private:
            sf::Font _font;
    };

}