/*
** PROJECT, 2024
** CPP_POOL
** File description:
** SpriteLoader.cpp
*/

#include "SpriteLoader.hpp"

namespace game {

    void SpriteLoader::loadAllTextures()
    {
        std::shared_ptr<std::map<SpriteType, sf::Texture>> textures = std::make_shared<std::map<SpriteType, sf::Texture>>();

        for (auto &spritePath : spritePaths) {
            try {
                sf::Texture texture = loadTexture(spritePath.second);
                textures->insert(std::make_pair(spritePath.first, texture));
            } catch (const Error &e) {
                std::cerr << e.what() << std::endl;
                exit(84);
            }
        }

        getTextures(textures);
    }

    sf::Texture SpriteLoader::loadTexture(const std::string &path) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::string errorMsg = "Failed to load texture from file: " + path;
            throw Error(errorMsg);
        }
        return texture;
    }

    std::shared_ptr<std::map<SpriteType, sf::Texture>> SpriteLoader::getTextures(
            const std::shared_ptr<std::map<SpriteType, sf::Texture>>& textures_to_load
    )
    {
        static std::shared_ptr<std::map<SpriteType, sf::Texture>> textures;
        if (textures_to_load != nullptr)
            textures = textures_to_load;
        else
            return textures;
        return nullptr;
    }

    sf::Sprite SpriteLoader::getSprite(SpriteType type) {
        return sf::Sprite(getTextures()->at(type));
    }

}