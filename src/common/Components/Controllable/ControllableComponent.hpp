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

            void setDirection(int direction);
            void setLastDirection(int direction);
            void setCanMove(int canMove);
            void setMap(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map);
            void setIsWall(std::array<bool, 4> isWall);

            int getDirection() const;
            int getLastDirection() const;
            int getCanMove() const;
            std::array<bool, 4> getIsWall() const;
            std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> getMap() const;

            sf::Keyboard::Key up;
            sf::Keyboard::Key down;
            sf::Keyboard::Key left;
            sf::Keyboard::Key right;

        protected:
            std::array<bool, 4> _isWall{};
            std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> _map;
        private:
            int _direction;
            int _lastDirection;
            int _canMove;
    };

}