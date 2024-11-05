/*
** PROJECT, 2024
** CPP_POOL
** File description:
** GhostSystem.cpp
*/

#include "GhostSystem.hpp"

namespace game {

    GhostSystem::GhostSystem() {}

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> GhostSystem::getEntities()
    {
        return _entities;
    }

    void GhostSystem::addEntity(std::shared_ptr<Entity> &entity)
    {
        _entities->push_back(entity);
    }

    void GhostSystem::update(int gameLevel, bool resetGame) {
        PositionComponent playerPosition;
        int playerDirection;
        int energizerTimer;

        if (resetGame) {
            reset(gameLevel);
        }

        for (auto &entity : *_entities) {
            if (entity->hasComponent<ControllableComponent>()) {
                playerPosition = entity->getComponent<PositionComponent>();
                playerDirection = entity->getComponent<RectableComponent>().getCurrentFrame();
                energizerTimer = entity->getComponent<ControllableComponent>().getEnergyTimer();
                continue;
            }
        }

        for (auto &entity : *_entities) {
            if (!entity->hasComponent<GhostComponent>())
                continue;
            auto &ghost = entity->getComponent<GhostComponent>();
            auto &velocity = entity->getComponent<VelocityComponent>();
            auto &render = entity->getComponent<RenderableComponent>();
            auto &rect = entity->getComponent<RectableComponent>();
            auto &pos = entity->getComponent<PositionComponent>();
            int optimal_direction = 4;
            int available_ways = 0;
            int speed = GHOST_SPEED;

            ghost.setAnimationTimer((1 + ghost.getAnimationTimer()) % (GHOST_ANIMATION_FRAMES * GHOST_ANIMATION_SPEED));
            ghost.setCanMove(false);

            manageFrightenedMode(ghost, pos, velocity, energizerTimer, gameLevel, speed);
            changeDisplay(ghost, render, rect, energizerTimer);
            findPlayer(ghost, pos, playerPosition, playerDirection);
            if (ghost.getFrightenedMode() != FRIGHTENED) {
                ghost.setCanMove(true);
                setDirection(velocity, ghost, pos, optimal_direction, available_ways);
            } else {
                slowGhost(ghost, velocity, rect, optimal_direction, available_ways);
            }

            if (ghost.canMove()) {
                if (!velocity.getIsWall()[ghost.getDirection()]) {
                    velocity.x = 0;
                    velocity.y = 0;
                    switch (ghost.getDirection()) {
                        case 0:
                            velocity.x = static_cast<float>(speed);
                            rect.setDirection(0);
                            break;
                        case 1:
                            velocity.y = -static_cast<float>(speed);
                            rect.setDirection(1);
                            break;
                        case 2:
                            velocity.x = -static_cast<float>(speed);
                            rect.setDirection(2);
                            break;
                        case 3:
                            velocity.y = static_cast<float>(speed);
                            rect.setDirection(3);
                            break;
                    }
                }
            } else {
                velocity.x = 0;
                velocity.y = 0;
            }
        }
    }

    void GhostSystem::slowGhost(GhostComponent &ghost, VelocityComponent &velocity, RectableComponent &rect, int &optimal_direction, int &available_ways) {
        int any_direction = rand() % 4;

        if (ghost.getFrightenedSpeedTimer() == 0) {
            ghost.setCanMove(true);
            ghost.setFrightenedSpeedTimer(GHOST_FRIGHTENED_SPEED);

            for (int i = 0; i < 4; i ++) {
                if (i == (2 + ghost.getDirection()) % 4) {
                    continue;
                } else if (!velocity.getIsWall()[i]) {
                    available_ways++;
                    break;
                }
            }

            if (available_ways > 0) {
                while (velocity.getIsWall()[any_direction] || any_direction == (2 + ghost.getDirection()) % 4) {
                    any_direction = rand() % 4;
                }
                ghost.setDirection(any_direction);
            } else {
                ghost.setDirection((2 + ghost.getDirection()) % 4);
            }

        } else {
            ghost.setFrightenedSpeedTimer(ghost.getFrightenedSpeedTimer() - 1);
        }
    }

    void GhostSystem::changeDisplay(GhostComponent &ghost, RenderableComponent &render, RectableComponent &rect, int energizerTimer) {
        auto body_frame = static_cast<unsigned char>(std::floor(static_cast<float>(ghost.getAnimationTimer()) / static_cast<float>(GHOST_ANIMATION_SPEED)));
        auto &sprite = render.getSprite();
        auto &face = render.getFace();

        if (ghost.getFrightenedMode() == NORMAL) {
            render.setDisplayBody(true);
            render.changeDisplayMode(ghost.getGhostId());
            face.setColor(sf::Color(255, 255, 255));
            rect.setRect(sf::IntRect(OBJECT_SIZE * ghost.getDirection(), OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
        } else if (ghost.getFrightenedMode() == FRIGHTENED) {
            sprite.setColor(sf::Color(36, 36, 255));
            rect.setRect(sf::IntRect(4 * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
            if (1 == GHOST_FLASH_START >= energizerTimer && 0 == body_frame % 2) {
                sprite.setColor(sf::Color(255, 255, 255));
                face.setColor(sf::Color(255, 0, 0));
            } else {
                sprite.setColor(sf::Color(36, 36, 255));
                face.setColor(sf::Color(255, 255, 255));
            }
        } else if (ghost.getFrightenedMode() == ESCAPE) {
            render.setDisplayBody(false);
            rect.setRect(sf::IntRect(OBJECT_SIZE * ghost.getDirection(), 2 * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
        }
    }

    void GhostSystem::manageFrightenedMode(GhostComponent &ghost, PositionComponent &pos, VelocityComponent &vel, int energizerTimer, int gameLevel, int &speed) {
        if (ghost.getFrightenedMode() == NORMAL && energizerTimer == ENERGIZER_DURATION / pow(2, gameLevel))
        {
            ghost.setFrightenedSpeedTimer(GHOST_FRIGHTENED_SPEED);
            ghost.setFrightenedMode(FRIGHTENED);
        }
        else if (0 == energizerTimer && ghost.getFrightenedMode() == FRIGHTENED)
        {
            ghost.setFrightenedMode(NORMAL);
        }

        if (ghost.getFrightenedMode() == ESCAPE && 0 == static_cast<int>(pos.x) % GHOST_ESCAPE_SPEED && 0 == static_cast<int>(pos.y) % GHOST_ESCAPE_SPEED)
        {
            speed = GHOST_ESCAPE_SPEED;
            speed = GHOST_ESCAPE_SPEED;
        }
    }

    void GhostSystem::setDirection(VelocityComponent &velocity, GhostComponent &ghost, PositionComponent &pos, int &optimal_direction, int &available_ways) {
        for (int i = 0; i < 4; i++) {
            if (i == (2 + ghost.getDirection()) % 4) {
                continue;
            } else if (!velocity.getIsWall()[i]) {
                if (optimal_direction == 4)
                    optimal_direction = i;
                available_ways++;
                if (findTarget(i, ghost, pos) < findTarget(optimal_direction, ghost, pos))
                    optimal_direction = i;
            }
        }
        if (available_ways > 1) {
            ghost.setDirection(optimal_direction);
        } else {
            if (optimal_direction == 4) {
                ghost.setDirection((2 + ghost.getDirection()) % 4);
            } else {
                ghost.setDirection(optimal_direction);
            }
        }
    }

    double GhostSystem::findTarget(int direction, GhostComponent &ghost, PositionComponent &pos) {
        double x = pos.x;
        double y = pos.y;

        switch (direction)
        {
            case 0:
                x += GHOST_SPEED;
                break;
            case 1:
                y -= GHOST_SPEED;
                break;
            case 2:
                x -= GHOST_SPEED;
                break;
            case 3:
                y += GHOST_SPEED;
                break;
            default:
                break;
        }

        return sqrt(pow(x - ghost.getTargetPosition().x, 2) + pow(y - ghost.getTargetPosition().y, 2));
    }

    void GhostSystem::sendToCorners(GhostComponent &ghost) {
        switch (ghost.getGhostId())
        {
            case 0:
                ghost.setTargetPosition({OBJECT_SIZE * (MAP_WIDTH - 1), 0});
                break;
            case 1:
                ghost.setTargetPosition({0, 0});
                break;
            case 2:
                ghost.setTargetPosition({OBJECT_SIZE * (MAP_WIDTH - 1), OBJECT_SIZE * (MAP_HEIGHT - 1)});
                break;
            case 3:
                ghost.setTargetPosition({0, OBJECT_SIZE * (MAP_HEIGHT - 1)});
                break;
            default:
                break;
        }
    }

    void GhostSystem::chaseMode(GhostComponent &ghost, PositionComponent &position, PositionComponent &playerPosition, int playerDirection) {
        pos targetPosition = ghost.getTargetPosition();
        pos ghost0Position{};

        switch (ghost.getGhostId())
        {
            case 0:
                ghost.setTargetPosition({playerPosition.x, playerPosition.y});
                break;
            case 1:
                targetPosition = {playerPosition.x, playerPosition.y};

                switch (playerDirection)
                {
                    case 0:
                        targetPosition.x += OBJECT_SIZE * GHOST_1_CHASE;
                        break;
                    case 1:
                        targetPosition.y -= OBJECT_SIZE * GHOST_1_CHASE;
                        break;
                    case 2:
                        targetPosition.x -= OBJECT_SIZE * GHOST_1_CHASE;
                        break;
                    case 3:
                        targetPosition.y += OBJECT_SIZE * GHOST_1_CHASE;
                        break;
                    default:
                        break;
                }
                ghost.setTargetPosition(targetPosition);
                break;
            case 2:
                targetPosition = {playerPosition.x, playerPosition.y};

                switch (playerDirection)
                {
                    case 0:
                        targetPosition.x += OBJECT_SIZE * GHOST_2_CHASE;
                        break;
                    case 1:
                        targetPosition.y -= OBJECT_SIZE * GHOST_2_CHASE;
                        break;
                    case 2:
                        targetPosition.x -= OBJECT_SIZE * GHOST_2_CHASE;
                        break;
                    case 3:
                        targetPosition.y += OBJECT_SIZE * GHOST_2_CHASE;
                        break;
                    default:
                        break;
                }

                for (auto &entity : *_entities) {
                    if (!entity->hasComponent<GhostComponent>())
                        continue;
                    auto &g = entity->getComponent<GhostComponent>();
                    auto &p = entity->getComponent<PositionComponent>();
                    if (g.getGhostId() == 0)
                    {
                        ghost0Position = p.getPos();
                        break;
                    }
                }

                targetPosition.x += targetPosition.x - ghost0Position.x;
                targetPosition.y += targetPosition.y - ghost0Position.y;

                ghost.setTargetPosition(targetPosition);
                break;
            case 3:
                if (OBJECT_SIZE * GHOST_3_CHASE <= sqrt(pow(position.x - playerPosition.x, 2) + pow(position.y - playerPosition.y, 2))) {
                    ghost.setTargetPosition({playerPosition.x, playerPosition.y});
                } else {
                    ghost.setTargetPosition({0, OBJECT_SIZE * (MAP_HEIGHT - 1)});
                }
                break;
            default:
                break;
        }
    }

    void GhostSystem::findPlayer(GhostComponent &ghost, PositionComponent &pos, PositionComponent &playerPosition, int playerDirection) {
        if (ghost.getUseDoor()) {
            if (pos.getPos() == ghost.getTargetPosition()) {
                if (ghost.getHomeExitPosition() == ghost.getTargetPosition()) {
                    ghost.setUseDoor(false);
                } else if (ghost.getHomePosition() == ghost.getTargetPosition()) {
                    ghost.setFrightenedMode(NORMAL);
                    ghost.setTargetPosition(ghost.getHomeExitPosition());
                }
            }
        } else {
            if (!ghost.getScatter()) {
                sendToCorners(ghost);
            } else {
                chaseMode(ghost, pos, playerPosition, playerDirection);
            }
        }
    }

    void GhostSystem::reset(int gameLevel) {
        std::array<pos, 4> ghostPos{};

        for (auto &entity : *_entities) {
            if (!entity->hasComponent<GhostComponent>())
                continue;
            auto &ghost = entity->getComponent<GhostComponent>();
            auto &pos = entity->getComponent<PositionComponent>();

            ghostPos[ghost.getGhostId()] = pos.getPos();
        }

        for (auto &entity : *_entities) {
            if (!entity->hasComponent<GhostComponent>())
                continue;
            auto &ghost = entity->getComponent<GhostComponent>();
            auto &vel = entity->getComponent<VelocityComponent>();

            ghost.setFrightenedMode(NORMAL);
            ghost.setFrightenedSpeedTimer(0);
            ghost.setUseDoor(0 < ghost.getGhostId());
            ghost.setScatter(false);
            ghost.setDirection(0);
            ghost.setAnimationTimer(0);
            ghost.setTargetPosition(ghostPos[0]);
            ghost.setHomePosition(ghostPos[2]);
            ghost.setHomeExitPosition(ghostPos[0]);

            vel.x = GHOST_SPEED;
            vel.y = 0;
        }
    }

}
