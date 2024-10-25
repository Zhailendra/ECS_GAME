/*
** PROJECT, 2024
** CPP_POOL
** File description:
** HitboxSystem.cpp
*/

#include "HitboxSystem.hpp"

namespace game {

    HitboxSystem::HitboxSystem() {}

    HitboxSystem::~HitboxSystem() {}

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> HitboxSystem::getEntities() {
        return _entities;
    }

    void HitboxSystem::addEntity(std::shared_ptr<Entity> &entity) {
        _entities->push_back(entity);
    }

    void HitboxSystem::update() {
        for (const std::shared_ptr<Entity> &entity : *_entities) {
            if (entity->hasComponent<RenderableComponent>() && entity->hasComponent<VelocityComponent>()) {
                checkPlayerHitbox(entity);
            }
        }
    }

    bool HitboxSystem::verifyNextPos(double x, double y, bool isPellet) {
        bool isWall = false;
        double x1 = x / OBJECT_SIZE;
        double y1 = y / OBJECT_SIZE;
        int x2, y2;

        for (int i = 0; i < 4; i++) {
            switch (i) {
                case 0:
                    x2 = static_cast<int>(std::floor(x1));
                    y2 = static_cast<int>(std::floor(y1));
                    break;
                case 1:
                    x2 = static_cast<int>(std::ceil(x1));
                    y2 = static_cast<int>(std::floor(y1));
                    break;
                case 2:
                    x2 = static_cast<int>(std::floor(x1));
                    y2 = static_cast<int>(std::ceil(y1));
                    break;
                case 3:
                    x2 = static_cast<int>(std::ceil(x1));
                    y2 = static_cast<int>(std::ceil(y1));
                    break;
            }

            if (x2 < MAP_WIDTH && y2 < MAP_HEIGHT) {
                checker(x2, y2, isWall, isPellet);
            }
        }

        return isWall;
    }

    void HitboxSystem::checkPlayerHitbox(const std::shared_ptr<Entity> &entity) {
        auto &velo = entity->getComponent<VelocityComponent>();
        auto &entityPos = entity->getComponent<PositionComponent>();
        std::array<bool, 4> isWall = {false, false, false, false};

        isWall[0] = verifyNextPos(entityPos.x + PLAYER_SPEED, entityPos.y, false);
        isWall[1] = verifyNextPos(entityPos.x, entityPos.y - PLAYER_SPEED, false);
        isWall[2] = verifyNextPos(entityPos.x - PLAYER_SPEED, entityPos.y, false);
        isWall[3] = verifyNextPos(entityPos.x, entityPos.y + PLAYER_SPEED, false);

        if (entity->hasComponent<ControllableComponent>()) {
            if (verifyNextPos(entityPos.x, entityPos.y, true)) {
                std::cout << "Energizer eaten" << std::endl;
            }
        }

        velo.setIsWall(isWall);
    }

    void HitboxSystem::checker(int x, int y, bool &isWall, bool isPellet) {
        std::vector<std::shared_ptr<Entity>> toRemove;

        for (const auto &entity : *_entities) {
            if (!entity->hasComponent<RenderableComponent>() && !entity->hasComponent<PositionComponent>())
                continue;
            if (!isPellet) {
                if (entity->hasComponent<WallsComponent>() || entity->hasComponent<DoorComponent>()) {
                    auto &entityPos = entity->getComponent<PositionComponent>();
                    if (x == (entityPos.x / OBJECT_SIZE) && y == (entityPos.y / OBJECT_SIZE)) {
                        isWall = true;
                    }
                }
            } else {
                if (entity->hasComponent<PelletsComponent>()) {
                    auto &entityPos = entity->getComponent<PositionComponent>();
                    if (x == (entityPos.x / OBJECT_SIZE) && y == (entityPos.y / OBJECT_SIZE)) {
                        toRemove.push_back(entity);
                    }
                } else if (entity->hasComponent<EnergizersComponent>()) {
                    auto &entityPos = entity->getComponent<PositionComponent>();
                    if (x == (entityPos.x / OBJECT_SIZE) && y == (entityPos.y / OBJECT_SIZE)) {
                        toRemove.push_back(entity);
                        isWall = true;
                    }
                }
            }
        }
        for (const auto &entity : toRemove) {
            EntityManager::destroyEntity(_entities, entity->getId());
        }
    }

}
