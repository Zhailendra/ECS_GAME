/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Map.cpp
*/

#include "Map.hpp"

namespace game {

    Map::Map()
    {
        _originalMap = {
                " ################### ",
                " #........#........# ",
                " #o##.###.#.###.##o# ",
                " #.................# ",
                " #.##.#.#####.#.##.# ",
                " #....#...#...#....# ",
                " ####.### # ###.#### ",
                "    #.#   0   #.#    ",
                "#####.# ##=## #.#####",
                "     .  #123#  .     ",
                "#####.# ##### #.#####",
                "    #.#       #.#    ",
                " ####.# ##### #.#### ",
                " #........#........# ",
                " #.##.###.#.###.##.# ",
                " #o.#.....P.....#.o# ",
                " ##.#.#.#####.#.#.## ",
                " #....#...#...#....# ",
                " #.######.#.######.# ",
                " #.................# ",
                " ################### "
        };
    }

    void Map::initMap()
    {
        _map = setMap();
    }

    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &Map::getMap()
    {
        return _map;
    }

    std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> Map::setMap()
    {
        for (unsigned char i = 0; i < MAP_HEIGHT; i++) {
            for (unsigned char j = 0; j < MAP_WIDTH; j++) {
                _newMap[j][i] = Cell::EMPTY;
                switch (_originalMap[i][j]) {
                    case '#':
                        _newMap[j][i] = Cell::WALL;
                        break;
                    case '=':
                        _newMap[j][i] = Cell::DOOR;
                        break;
                    case '.':
                        _newMap[j][i] = Cell::PELLET;
                        break;
                    case 'o':
                        _newMap[j][i] = Cell::ENERGIZER;
                        break;
                    case 'P':
                        _playerPos.x = OBJECT_SIZE * j;
                        _playerPos.y = OBJECT_SIZE * i;
                        break;
                    case '0':
                        _enemiesPos[0].x = OBJECT_SIZE * j;
                        _enemiesPos[0].y = OBJECT_SIZE * i;
                        break;
                    case '1':
                        _enemiesPos[1].x = OBJECT_SIZE * j;
                        _enemiesPos[1].y = OBJECT_SIZE * i;
                        break;
                    case '2':
                        _enemiesPos[2].x = OBJECT_SIZE * j;
                        _enemiesPos[2].y = OBJECT_SIZE * i;
                        break;
                    case '3':
                        _enemiesPos[3].x = OBJECT_SIZE * j;
                        _enemiesPos[3].y = OBJECT_SIZE * i;
                        break;
                }
            }
        }
        return _newMap;
    }

    pos Map::getPlayerPos() const {
        return _playerPos;
    }

    bool Map::isWallUp() const {
        return _isWallUp;
    }

    bool Map::isWallDown() const {
        return _isWallDown;
    }

    bool Map::isWallRight() const {
        return _isWallRight;
    }

    bool Map::isWallLeft() const {
        return _isWallLeft;
    }

}