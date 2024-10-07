/*
** PROJECT, 2024
** CPP_POOL
** File description:
** ASystem.cpp
*/

#include "ASystem.hpp"

#include <utility>

namespace game {

    ASystem::ASystem() {
    }

    ASystem::~ASystem() {
    }

    void ASystem::setEntities(std::shared_ptr<std::vector<std::shared_ptr<Entity>>> entities) {
        _entities = std::move(entities);
    }

    void ASystem::setInputs(std::shared_ptr<std::vector<sf::Event>> &inputs) {
        _inputs = inputs;
    }

}
