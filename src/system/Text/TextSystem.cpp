/*
** PROJECT, 2024
** CPP_POOL
** File description:
** TextSystem.cpp
*/

#include "TextSystem.hpp"

namespace game {

    TextSystem::TextSystem()
    {
        if (!_font.loadFromFile(FONT_TTF))
            throw std::runtime_error("Cannot load font");
    }

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> TextSystem::getEntities()
    {
        return _entities;
    }

    void TextSystem::addEntity(std::shared_ptr<Entity> &entity)
    {
        _entities->push_back(entity);
    }

    void TextSystem::update(int gameLevel, bool resetGame) {
        for (auto &entity : *_entities) {
            if (!entity->hasComponent<TextComponent>())
                continue;
            auto &text = entity->getComponent<TextComponent>();
            const auto &pos = entity->getComponent<PositionComponent>();
            if (!text.getIsFontLoaded()) {
                text.getText().setFont(_font);
                text.setIsFontLoaded(true);
            }

            text.getText().setPosition(static_cast<float>(pos.x), static_cast<float>(pos.y));
            text.getText().setString(text.getString());
        }
    }

}
