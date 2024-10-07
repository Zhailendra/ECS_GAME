/*
** PROJECT, 2024
** CPP_POOL
** File description:
** SpriteLoader.hpp
*/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Path.hpp"
#include "Exception.hpp"

namespace game {
    class SpriteLoader {
        public:
            static void loadAllTextures();
            static std::shared_ptr<std::map<SpriteType, sf::Texture>> getTextures(const std::shared_ptr<std::map<SpriteType, sf::Texture>>& textures_to_load = nullptr);
            static sf::Sprite getSprite(SpriteType type);
        private:
            static sf::Texture loadTexture(const std::string &path);
    };
};
