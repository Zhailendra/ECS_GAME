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
            if (entity->hasComponent<RenderableComponent>() && entity->hasComponent<ControllableComponent>()) {
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
                for (size_t size = 0; size < _entities->size(); size++) {
                    std::shared_ptr<Entity> &entity = _entities->at(size);
                    if (!entity->hasComponent<RenderableComponent>() && !entity->hasComponent<PositionComponent>())
                        continue;
                    if (!isPellet) {
                        if (entity->hasComponent<WallsComponent>() || entity->hasComponent<DoorComponent>()) {
                            auto &entityPos = entity->getComponent<PositionComponent>();
                            if (x2 == (entityPos.x / OBJECT_SIZE) && y2 == (entityPos.y / OBJECT_SIZE)) {
                                isWall = true;
                            }
                        }
                    } else {
                        if (entity->hasComponent<PelletsComponent>()) {
                            auto &entityPos = entity->getComponent<PositionComponent>();
                            if (x2 == (entityPos.x / OBJECT_SIZE) && y2 == (entityPos.y / OBJECT_SIZE)) {
                                EntityManager::destroyEntity(_entities, entity->getId());
                            }
                        } else if (entity->hasComponent<EnergizersComponent>()) {
                            auto &entityPos = entity->getComponent<PositionComponent>();
                            if (x2 == (entityPos.x / OBJECT_SIZE) && y2 == (entityPos.y / OBJECT_SIZE)) {
                                EntityManager::destroyEntity(_entities, entity->getId());
                                isWall = true;
                            }
                        }
                    }
                }
            }
        }

        return isWall;
    }

    void HitboxSystem::checkPlayerHitbox(const std::shared_ptr<Entity> &player) {
        auto &controllable = player->getComponent<ControllableComponent>();
        auto &playerPos = player->getComponent<PositionComponent>();
        std::array<bool, 4> isWall = {false, false, false, false};

        isWall[0] = verifyNextPos(playerPos.x + PLAYER_SPEED, playerPos.y, false);
        isWall[1] = verifyNextPos(playerPos.x, playerPos.y - PLAYER_SPEED, false);
        isWall[2] = verifyNextPos(playerPos.x - PLAYER_SPEED, playerPos.y, false);
        isWall[3] = verifyNextPos(playerPos.x, playerPos.y + PLAYER_SPEED, false);
        if (verifyNextPos(playerPos.x, playerPos.y, true)) {
            std::cout << "Energizer eaten" << std::endl;
        }

        controllable.setIsWall(isWall);
    }

}
