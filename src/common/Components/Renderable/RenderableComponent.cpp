/*
** PROJECT, 2024
** CPP_POOL
** File description:
** RenderableComponent.cpp
*/

#include "RenderableComponent.hpp"

namespace game {

    RenderableComponent::RenderableComponent()
    {
        _type = RENDERABLE;
    }

    RenderableComponent::RenderableComponent(SpriteType spriteType)
    {
        _type = RENDERABLE;
        _spriteType = spriteType;
        auto textures = SpriteLoader::getTextures();
        if (textures == nullptr)
            throw Error("No textures loaded");
        _sprite.setTexture(textures->at(spriteType));
    }

    sf::IntRect RenderableComponent::getHitbox() {
        return sf::IntRect(
                static_cast<int>(_sprite.getPosition().x),
                static_cast<int>(_sprite.getPosition().y),
                OBJECT_SIZE, OBJECT_SIZE
        );
    }

}