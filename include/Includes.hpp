/*
** PROJECT, 2023
**
** File description:
** Includes.hpp
*/

#pragma once

/* libraries */

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <array>
#include <cmath>

/* Struct */

struct pos {

    double x;
    double y;

    bool operator==(const pos &other) const {
        return x == other.x && y == other.y;
    }
};

/* Const */

constexpr int MAP_HEIGHT = 21;
constexpr int MAP_WIDTH = 21;
constexpr int WINDOW_RESIZE = 2;
constexpr int OBJECT_SIZE = 16;
constexpr int FONT_SIZE = 16;
