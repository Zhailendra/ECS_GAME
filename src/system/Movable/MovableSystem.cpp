/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Movable.cpp
*/

#include "MovableSystem.hpp"

namespace game {

    MovableSystem::MovableSystem()
    {
    }

    MovableSystem::~MovableSystem()
    {
    }

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> MovableSystem::getEntities()
    {
        return _entities;
    }

    void MovableSystem::addEntity(std::shared_ptr<Entity> &entity)
    {
        _entities->push_back(entity);
    }

    void MovableSystem::update() {
        for (auto & entity : *_entities) {
            if (!entity->hasComponent<PositionComponent>() || !entity->hasComponent<VelocityComponent>() || entity->hasComponent<WallsComponent>() || entity->hasComponent<DoorComponent>() || entity->hasComponent<PelletsComponent>() || entity->hasComponent<EnergizersComponent>())
                continue;
            if (entity->hasComponent<ControllableComponent>()) {
                auto &controllable = entity->getComponent<ControllableComponent>();
                if (!controllable.getIsPlaying())
                    continue;
                auto &pos = entity->getComponent<PositionComponent>();
                auto &vel = entity->getComponent<VelocityComponent>();
                pos.setPos(pos.x + vel.x, pos.y + vel.y);
            } else if (entity->hasComponent<GhostComponent>()){
                auto &pos = entity->getComponent<PositionComponent>();
                auto &vel = entity->getComponent<VelocityComponent>();
                pos.setPos(pos.x + vel.x, pos.y + vel.y);
            }
        }
    }

}
