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

    RenderableComponent::RenderableComponent(SpriteType spriteType, int ghostId) {
        _type = RENDERABLE;
        _spriteType = spriteType;
        auto textures = SpriteLoader::getTextures();
        if (textures == nullptr)
            throw Error("No textures loaded");
        _sprite.setTexture(textures->at(spriteType));
        _face.setTexture(textures->at(spriteType));
        switch (ghostId) {
            case 0:
                _sprite.setColor(sf::Color(255, 0, 0));
                break;
            case 1:
                _sprite.setColor(sf::Color(255, 182, 255));
                break;
            case 2:
                _sprite.setColor(sf::Color(0, 255, 255));
                break;
            case 3:
                _sprite.setColor(sf::Color(255, 182, 85));
                break;
            default:
                break;
        }
    }

    sf::IntRect RenderableComponent::getHitbox() {
        return sf::IntRect(
                static_cast<int>(_sprite.getPosition().x),
                static_cast<int>(_sprite.getPosition().y),
                OBJECT_SIZE, OBJECT_SIZE
        );
    }

}