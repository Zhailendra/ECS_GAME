/*
** PROJECT, 2024
** CPP_POOL
** File description:
** GhostSystem.cpp
*/

#include "GhostSystem.hpp"

namespace game {

    GhostSystem::GhostSystem() : _direction(0) {}

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> GhostSystem::getEntities()
    {
        return _entities;
    }

    void GhostSystem::addEntity(std::shared_ptr<Entity> &entity)
    {
        _entities->push_back(entity);
    }

    void GhostSystem::update() {
        for (auto &entity : *_entities) {
            if (entity->hasComponent<GhostComponent>()) {
                auto &ghost = entity->getComponent<GhostComponent>();
                auto &velocity = entity->getComponent<VelocityComponent>();
                auto &rect = entity->getComponent<RectableComponent>();
                auto &pos = entity->getComponent<PositionComponent>();
                ghost.setAnimationTimer((1 + ghost.getAnimationTimer()) % (GHOST_ANIMATION_FRAMES * GHOST_ANIMATION_SPEED));

                if (!velocity.getIsWall()[_direction]) {
                    velocity.x = 0;
                    velocity.y = 0;
                    switch (_direction) {
                        case 0:
                            velocity.x = GHOST_SPEED;
                            rect.setDirection(0);
                            break;
                        case 1:
                            velocity.y = -GHOST_SPEED;
                            rect.setDirection(1);
                            break;
                        case 2:
                            velocity.x = -GHOST_SPEED;
                            rect.setDirection(2);
                            break;
                        case 3:
                            velocity.y = GHOST_SPEED;
                            rect.setDirection(3);
                            break;
                    }
                } else {
                    velocity.x = 0;
                    velocity.y = 0;
                }

                if (-OBJECT_SIZE >= pos.x) {
                    pos.setPos(OBJECT_SIZE * MAP_WIDTH - GHOST_SPEED, pos.y);
                } else if (OBJECT_SIZE * MAP_WIDTH <= pos.x) {
                    pos.setPos(GHOST_SPEED - OBJECT_SIZE, pos.y);
                }
            }
        }
    }

}
