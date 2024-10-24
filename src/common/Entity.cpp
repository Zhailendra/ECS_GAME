/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

namespace game {

    bool displayWinText = false;

    Entity::Entity(std::uint32_t id) : _id(id) {}

    Entity::~Entity() {}

    std::uint32_t Entity::getId() const
    {
        return _id;
    }

    void Entity::setId(std::uint32_t id)
    {
        _id = id;
    }

}