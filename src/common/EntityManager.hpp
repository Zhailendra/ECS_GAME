/*
** PROJECT, 2024
** CPP_POOL
** File description:
** EntityManager.hpp
*/

#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>
#include <random>

#include "Entity.hpp"
#include "Position/PositionComponent.hpp"
#include "Controllable/ControllableComponent.hpp"
#include "Rectable/RectableComponent.hpp"
#include "Renderable/RenderableComponent.hpp"
#include "Velocity/VelocityComponent.hpp"
#include "Walls/WallsComponent.hpp"
#include "Pellets/PelletsComponent.hpp"
#include "Energizers/EnergizersComponent.hpp"
#include "Door/DoorComponent.hpp"
#include "Text/TextComponent.hpp"
#include "Ghost/GhostComponent.hpp"

namespace game {

    class EntityManager {
        public:
            using MaxEntities = std::uint32_t;

            EntityManager();
            ~EntityManager() = default;

            std::shared_ptr<Entity> createEntity();
            static void destroyEntity(const std::shared_ptr<std::vector<std::shared_ptr<Entity>>>&, std::uint32_t entityToDestroy);
            void clearEntities();

            std::shared_ptr<Entity> getEntity(std::uint32_t entityId) const;
            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getEntities() const;
            std::queue<std::uint32_t> getAvailableEntities() const;

            size_t getSize() const;

            std::shared_ptr<Entity> createPlayer(const pos &playerPos);
            std::shared_ptr<Entity> createPlayerDeath(const pos &playerPos);
            std::shared_ptr<Entity> createGhosts(const std::array<pos, 4> &ghostPos);

            std::shared_ptr<Entity> createWall(const pos &wallPos, sf::IntRect rect);
            std::shared_ptr<Entity> createPellet(const pos &pelletPos, sf::IntRect rect);
            std::shared_ptr<Entity> createEnergizer(const pos &energizerPos, sf::IntRect rect);
            std::shared_ptr<Entity> createDoor(const pos &doorPos, sf::IntRect rect);

            std::shared_ptr<Entity> createText(const pos &textPos, const std::string &text, const sf::Color &color, unsigned int size, bool display, bool displayNow, bool isGameOverText);

        protected:
        private:
            std::shared_ptr<std::vector<std::shared_ptr<Entity>>> _entities;
            std::queue<std::uint32_t> _availableEntities;
            std::uniform_int_distribution<std::uint32_t> _distribution;
            std::mt19937 _generator;

    };

}