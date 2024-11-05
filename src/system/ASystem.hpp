/*
** PROJECT, 2024
** CPP_POOL
** File description:
** ASystem.hpp
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "ISystem.hpp"
#include "Entity.hpp"

constexpr int PLAYER_ANIM_SPEED = 4;
constexpr int PLAYER_ANIM_FRAME = 6;
constexpr int PLAYER_DEATH_FRAME = 12;
constexpr int PLAYER_SPEED = 2;

constexpr int GHOST_SPEED = 1;

constexpr int SLOW_TIMER = 521;

namespace game {
    class ASystem : public ISystem {
        public:
            ASystem();
            virtual ~ASystem() = 0;

            virtual std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() = 0;
            virtual void addEntity(std::shared_ptr<Entity> &entity) = 0;
            virtual void setEntities(std::shared_ptr<std::vector<std::shared_ptr<Entity>>> entities);

            void setInputs(std::shared_ptr<std::vector<sf::Event>> &inputs);

            virtual void update(int gameLevel, bool resetGame) = 0;

        protected:
            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> _entities;
            std::shared_ptr<std::vector<sf::Event>> _inputs;

        private:
    };
}