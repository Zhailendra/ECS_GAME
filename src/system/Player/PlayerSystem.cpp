/*
** PROJECT, 2024
** CPP_POOL
** File description:
** PlayerSystem.cpp
*/

#include "PlayerSystem.hpp"

namespace game {

    PlayerSystem::PlayerSystem() : _animTime(0), _nbPellets(0)
    {
    }

    PlayerSystem::~PlayerSystem()
    {
    }

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PlayerSystem::getEntities() {
        return this->_entities;
    }

    void PlayerSystem::update() {
        for (auto &entity : *_entities) {
            if (!entity->hasComponent<ControllableComponent>())
                continue;
            auto &controllable = entity->getComponent<ControllableComponent>();
            auto &velocity = entity->getComponent<VelocityComponent>();
            auto &rect = entity->getComponent<RectableComponent>();

            rect.setFrameSpeed(std::floor(float(_animTime) / static_cast<float>(PLAYER_ANIM_SPEED)));
            _animTime = (1 + _animTime) % (PLAYER_ANIM_FRAME * PLAYER_ANIM_SPEED);

            for (sf::Event &ev : *_inputs) {
                if (ev.type == sf::Event::KeyPressed) {
                    setDirection(controllable);
                }
            }

            if (!controllable.getIsWall()[_dir.direction]) {
                velocity.x = 0;
                velocity.y = 0;
                switch (_dir.direction) {
                    case 0:
                        velocity.x = PLAYER_SPEED;
                        rect.setDirection(0);
                        break;
                    case 1:
                        velocity.y = -PLAYER_SPEED;
                        rect.setDirection(1);
                        break;
                    case 2:
                        velocity.x = -PLAYER_SPEED;
                        rect.setDirection(2);
                        break;
                    case 3:
                        velocity.y = PLAYER_SPEED;
                        rect.setDirection(3);
                        break;
                }
            } else {
                velocity.x = 0;
                velocity.y = 0;
            }
        }
    }

    void PlayerSystem::setDirection(ControllableComponent &controllable) {
        if (sf::Keyboard::isKeyPressed(controllable.up)) {
            !controllable.getIsWall()[1] ? _dir.direction = 1 : 0;
        } else if (sf::Keyboard::isKeyPressed(controllable.down)) {
            !controllable.getIsWall()[3] ? _dir.direction = 3 : 0;
        } else if (sf::Keyboard::isKeyPressed(controllable.left)) {
            !controllable.getIsWall()[2] ? _dir.direction = 2 : 0;
        } else if (sf::Keyboard::isKeyPressed(controllable.right)) {
            !controllable.getIsWall()[0] ? _dir.direction = 0 : 0;
        }
    }

}