/*
** PROJECT, 2024
** CPP_POOL
** File description:
** RenderableComponent.hpp
*/

#pragma once

#include <iostream>
#include "AComponent.hpp"
#include "SpriteLoader.hpp"

namespace game {

    class RenderableComponent : public AComponent {
        public:
            RenderableComponent();
            explicit RenderableComponent(SpriteType spriteType);
            ~RenderableComponent() = default;

            sf::FloatRect getGlobalBounds() { return _sprite.getGlobalBounds(); }
            sf::Sprite &getSprite() { return _sprite; }
            sf::IntRect getHitbox();

        protected:
            SpriteType _spriteType;
            sf::Sprite _sprite;
            sf::IntRect _hitbox;
    };

}