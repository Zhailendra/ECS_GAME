/*
** PROJECT, 2024
** CPP_POOL
** File description:
** ControllableComponent.hpp
*/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

#include "AComponent.hpp"
#include "Types.hpp"
#include "Map.hpp"

namespace game {

    class ControllableComponent : public AComponent {
        public:
            ControllableComponent(sf::Keyboard::Key up, sf::Keyboard::Key down,
                                  sf::Keyboard::Key left, sf::Keyboard::Key right);
            ControllableComponent() { _type = Components::CONTROLLABLE; }
            ~ControllableComponent();

            void setIsPlaying(bool isPlaying);

            bool getIsPlaying() const;

            sf::Keyboard::Key up;
            sf::Keyboard::Key down;
            sf::Keyboard::Key left;
            sf::Keyboard::Key right;

        protected:
        private:
            bool _isPlaying;
    };

}