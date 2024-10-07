/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Map.cpp
*/

#include "Map.hpp"

namespace game {

    Map::Map() : _nbPellets(0)
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
        _nbPellets = 0;
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
                        _nbPellets++;
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
        //_pacman->setNbPellets(_nbPellets);
        return _newMap;
    }

/*    void Map::drawMap()
    {
        for (unsigned char i = 0; i < MAP_WIDTH; i++) {
            for (unsigned char j = 0; j < MAP_HEIGHT; j++) {
                sprite.setPosition(static_cast<float>(OBJECT_SIZE * i), static_cast<float>(OBJECT_SIZE * j));
                switch (_map[i][j]) {
                    case Cell::WALL:
                        setAllWalls();
                        (j < MAP_HEIGHT - 1) ? (Cell::WALL == _map[i][1 + j]) ? _isWallDown = true : 0 : 0;
                        (0 < i) ? (Cell::WALL == _map[i - 1][j]) ? _isWallLeft = true : 0 : _isWallLeft = true;
                        (i < MAP_WIDTH - 1) ? (Cell::WALL == _map[1 + i][j]) ? _isWallRight = true : 0 : _isWallRight = true;
                        (0 < j) ? (Cell::WALL == _map[i][j - 1]) ? _isWallUp = true : 0 : 0;
                        sprite.setTextureRect(sf::IntRect(OBJECT_SIZE * (_isWallDown + 2 * (_isWallLeft + 2 * (_isWallRight + 2 * _isWallUp))), 0, OBJECT_SIZE, OBJECT_SIZE));
                        window.draw(sprite);
                        break;
                    case Cell::DOOR:
                        sprite.setTextureRect(sf::IntRect(2 * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
                        window.draw(sprite);
                        break;
                    case Cell::PELLET:
                        sprite.setTextureRect(sf::IntRect(0, OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
                        window.draw(sprite);
                        break;
                    case Cell::ENERGIZER:
                        sprite.setTextureRect(sf::IntRect(OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
                        window.draw(sprite);
                        break;
                    case Cell::EMPTY:
                        break;
                }
            }
        }
    }*/

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