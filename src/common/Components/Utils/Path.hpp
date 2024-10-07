#pragma once

#include <cstdint>
#include <map>
#include <string>

#define FONT_PATH "assets/Font.png"
#define FONT_TTF "assets/PacFont.ttf"

#define MAP_PATH "assets/Map.png"

#define PLAYER_PATH "assets/Pacman.png"
#define PLAYER_DEATH_PATH "assets/PacmanDeath.png"


enum SpriteType : std::uint16_t {
    FONT = 0,
    MAP = 1,
    PLAYER = 2,
    PLAYER_DEATH = 3,
};

static const std::map<SpriteType, std::string> spritePaths = {
        {FONT, FONT_PATH},
        {MAP, MAP_PATH},
        {PLAYER, PLAYER_PATH},
        {PLAYER_DEATH, PLAYER_DEATH_PATH}
};