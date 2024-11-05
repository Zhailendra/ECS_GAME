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

    void HitboxSystem::update(int gameLevel, bool resetGame) {
        for (const std::shared_ptr<Entity> &entity : *_entities) {
            if (entity->hasComponent<RenderableComponent>() && entity->hasComponent<VelocityComponent>()) {
                checkPlayerHitbox(entity, gameLevel);
            }
        }
    }

    bool HitboxSystem::verifyNextPos(double x, double y, bool isPellet, bool useDoor) {
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
                default:
                    break;
            }

            if (x2 < MAP_WIDTH && y2 < MAP_HEIGHT) {
                checker(x2, y2, isWall, isPellet, useDoor);
            }
        }

        return isWall;
    }

    void HitboxSystem::checkPlayerHitbox(const std::shared_ptr<Entity> &entity, int gameLevel) {
        auto &velo = entity->getComponent<VelocityComponent>();
        auto &entityPos = entity->getComponent<PositionComponent>();
        std::array<bool, 4> isWall = {false, false, false, false};
        int speed = (entity->hasComponent<ControllableComponent>() ? PLAYER_SPEED : GHOST_SPEED);
        bool useDoor = entity->hasComponent<GhostComponent>() && entity->getComponent<GhostComponent>().getUseDoor();

        isWall[0] = verifyNextPos(entityPos.x + speed, entityPos.y, false, useDoor);
        isWall[1] = verifyNextPos(entityPos.x, entityPos.y - speed, false, useDoor);
        isWall[2] = verifyNextPos(entityPos.x - speed, entityPos.y, false, useDoor);
        isWall[3] = verifyNextPos(entityPos.x, entityPos.y + speed, false, useDoor);

        if (-OBJECT_SIZE >= entityPos.x) {
            entityPos.setPos(OBJECT_SIZE * MAP_WIDTH - speed, entityPos.y);
        } else if (OBJECT_SIZE * MAP_WIDTH <= entityPos.x) {
            entityPos.setPos(speed - OBJECT_SIZE, entityPos.y);
        }

        if (entity->hasComponent<ControllableComponent>()) {
            auto &player = entity->getComponent<ControllableComponent>();
            if (verifyNextPos(entityPos.x, entityPos.y, true, useDoor)) {
                std::cout << "Energizer eaten" << std::endl;
                player.setEnergyTimer(static_cast<int>(ENERGIZER_DURATION / pow(2, gameLevel)));
            } else {
                player.setEnergyTimer(std::max(0, player.getEnergyTimer() - 1));
            }
            checkIfPlayerHitGhost(entityPos.x, entityPos.y, player);
        }

        velo.setIsWall(isWall);
    }

    void HitboxSystem::checkIfPlayerHitGhost(double x, double y, ControllableComponent &player) {
        for (const auto &entity : *_entities) {
            if (entity->hasComponent<RenderableComponent>() && entity->hasComponent<GhostComponent>()) {
                auto &ghost = entity->getComponent<GhostComponent>();
                auto &entityPos = entity->getComponent<PositionComponent>();
                if (entityPos.x > x - OBJECT_SIZE && entityPos.x < OBJECT_SIZE + x) {
                    if (entityPos.y > y - OBJECT_SIZE && entityPos.y < OBJECT_SIZE + y) {
                        if (ghost.getFrightenedMode() == NORMAL) {
                            player.setIsDead(true);
                        } else {
                            ghost.setUseDoor(true);
                            ghost.setFrightenedMode(ESCAPE);
                            ghost.setTargetPosition(ghost.getHomePosition());
                        }
                    }
                }
            }
        }
    }

    void HitboxSystem::checker(int x, int y, bool &isWall, bool isPellet, bool useDoor) {
        for (const auto &entity : *_entities) {
            if (!entity->hasComponent<RenderableComponent>() && !entity->hasComponent<PositionComponent>())
                continue;
            if (!isPellet) {
                if (entity->hasComponent<WallsComponent>() || (entity->hasComponent<DoorComponent>() && !useDoor)) {
                    auto &entityPos = entity->getComponent<PositionComponent>();
                    if (x == (entityPos.x / OBJECT_SIZE) && y == (entityPos.y / OBJECT_SIZE)) {
                        isWall = true;
                    }
                }
            } else {
                if (entity->hasComponent<PelletsComponent>()) {
                    auto &renderable = entity->getComponent<RenderableComponent>();
                    auto &pellet = entity->getComponent<PelletsComponent>();
                    auto &entityPos = entity->getComponent<PositionComponent>();
                    if (x == (entityPos.x / OBJECT_SIZE) && y == (entityPos.y / OBJECT_SIZE)) {
                        renderable.setDisplayable(false);
                        pellet.setIsEaten(true);
                    }
                } else if (entity->hasComponent<EnergizersComponent>()) {
                    auto &renderable = entity->getComponent<RenderableComponent>();
                    auto &energizer = entity->getComponent<EnergizersComponent>();
                    auto &entityPos = entity->getComponent<PositionComponent>();
                    if (x == (entityPos.x / OBJECT_SIZE) && y == (entityPos.y / OBJECT_SIZE) && !energizer.isAlreadyConsumed()) {
                        renderable.setDisplayable(false);
                        energizer.setIsEaten(true);
                        energizer.setAlreadyConsumed(true);
                        isWall = true;
                    }
                }
            }
        }
    }

}
