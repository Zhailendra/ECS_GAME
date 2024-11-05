/*
** PROJECT, 2024
** CPP_POOL
** File description:
** RectableSystem.cpp
*/

#include "RectableSystem.hpp"

namespace game {

    RectableSystem::RectableSystem()
    {
    }

    RectableSystem::~RectableSystem()
    {
    }

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> RectableSystem::getEntities()
    {
        return _entities;
    }

    void RectableSystem::addEntity(std::shared_ptr<Entity> &entity)
    {
        _entities->push_back(entity);
    }

    void RectableSystem::update(int gameLevel, bool resetGame)
    {
        for (auto & entity : *_entities) {
            if (!entity->hasComponent<RenderableComponent>() || !entity->hasComponent<RectableComponent>())
                continue;
            if (entity->hasComponent<WallsComponent>() || entity->hasComponent<PelletsComponent>() || entity->hasComponent<EnergizersComponent>() || entity->hasComponent<DoorComponent>())
                continue;
            if (entity->hasComponent<ControllableComponent>()) {
                auto &renderable = entity->getComponent<RenderableComponent>();
                auto &rectable = entity->getComponent<RectableComponent>();
                auto &controllable = entity->getComponent<ControllableComponent>();
                sf::Sprite &sprite = renderable.getSprite();

                if (controllable.getIsPlaying()) {
                    sprite.setTextureRect(sf::IntRect(OBJECT_SIZE * static_cast<int>(rectable.getFrameSpeed()),
                                                      OBJECT_SIZE * rectable.getCurrentFrame(), OBJECT_SIZE,
                                                      OBJECT_SIZE));
                } else {
                    sprite.setTextureRect(sf::IntRect(OBJECT_SIZE * static_cast<int>(rectable.getFrameSpeed()), 0, OBJECT_SIZE, OBJECT_SIZE));
                }
            }
            if (entity->hasComponent<GhostComponent>()) {
                auto &renderable = entity->getComponent<RenderableComponent>();
                auto &ghost = entity->getComponent<GhostComponent>();
                auto &rectable = entity->getComponent<RectableComponent>();
                auto body_frame = static_cast<unsigned char>(std::floor(static_cast<float>(ghost.getAnimationTimer()) / static_cast<float>(GHOST_ANIMATION_SPEED)));
                sf::Sprite &sprite = renderable.getSprite();
                sf::Sprite &face = renderable.getFace();

                sprite.setTextureRect(sf::IntRect(OBJECT_SIZE * body_frame, 0, OBJECT_SIZE, OBJECT_SIZE));
                face.setTextureRect(rectable.getRect());
            }
        }
    }

}
