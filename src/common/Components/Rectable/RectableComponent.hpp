/*
** PROJECT, 2024
** CPP_POOL
** File description:
** RectableComponent.hpp
*/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "AComponent.hpp"
#include "Types.hpp"

namespace game {

    class RectableComponent : public AComponent {
        public:
            RectableComponent() { _type = Components::RECTABLE; };

            explicit RectableComponent(int frameNumber);
            explicit RectableComponent(sf::IntRect rect);
            ~RectableComponent() override = default;

            void setDirection(int direction);
            void setFrameSpeed(float frameSpeed);
            void setRect(sf::IntRect rect);

            int getCurrentFrame() const;
            float getFrameSpeed() const;
            sf::IntRect getRect() const;

            friend std::ostream &operator<<(std::ostream &os, const RectableComponent &rectable);

            sf::Clock _keyHoldClock;
            sf::Clock _frameClock;
            bool _upKeyPressed = false;
            bool _downKeyPressed = false;
        private:
            sf::IntRect _rect;
            int _currentPlayerFrame = 0;
            float _animFrameSpeed = 0;
    };

}
