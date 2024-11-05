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
            explicit RenderableComponent(SpriteType spriteType, bool isGhost);
            ~RenderableComponent() = default;

            void changeDisplayMode(int ghostId);
            void setDisplayBody(bool displayBody) { _displayBody = displayBody; }
            void setDisplayable(bool displayable) { _displayable = displayable; }

            sf::FloatRect getGlobalBounds() { return _sprite.getGlobalBounds(); }
            sf::Sprite &getSprite() { return _sprite; }
            SpriteType getSpriteType() const { return _spriteType; }
            sf::Sprite &getFace() { return _face; }
            sf::IntRect getHitbox();
            bool getDisplayBody() const { return _displayBody; }
            bool getDisplayable() const { return _displayable; }

        protected:
            SpriteType _spriteType;
            sf::Sprite _sprite;
            sf::Sprite _face;
            sf::IntRect _hitbox;
            bool _displayBody;
            bool _displayable;
    };

}