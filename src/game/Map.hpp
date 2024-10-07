/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Map.hpp
*/

#pragma once

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

#include  "Includes.hpp"

enum Cell {
    WALL,
    DOOR,
    PELLET,
    ENERGIZER,
    EMPTY
};

namespace game {

    class Map {
        public:
            Map();
            ~Map() = default;

            void initMap();

            std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &getMap();
            std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> setMap();

            pos getPlayerPos() const;

            bool isWallUp() const;
            bool isWallDown() const;
            bool isWallRight() const;
            bool isWallLeft() const;

        protected:
        private:
            std::array<std::string, MAP_HEIGHT> _originalMap;
            std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> _map{};
            std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> _newMap{};

            pos _playerPos;
            std::array<pos, 4> _enemiesPos;

            bool _isWallUp{};
            bool _isWallDown{};
            bool _isWallRight{};
            bool _isWallLeft{};
    };

}