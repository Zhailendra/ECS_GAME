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
        _displayBody = true;
        _displayable = true;
    }

    RenderableComponent::RenderableComponent(SpriteType spriteType, bool isGhost)
    {
        _type = RENDERABLE;
        _spriteType = spriteType;
        _displayBody = true;
        _displayable = true;
        auto textures = SpriteLoader::getTextures();
        if (textures == nullptr)
            throw Error("No textures loaded");
        _sprite.setTexture(textures->at(spriteType));
        if (isGhost)
            _face.setTexture(textures->at(spriteType));
    }

    sf::IntRect RenderableComponent::getHitbox() {
        return sf::IntRect(
                static_cast<int>(_sprite.getPosition().x),
                static_cast<int>(_sprite.getPosition().y),
                OBJECT_SIZE, OBJECT_SIZE
        );
    }

    void RenderableComponent::changeDisplayMode(int ghostId) {
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

}