/*
** PROJECT, 2024
** CPP_POOL
** File description:
** EntityManager.cpp
*/

#include "EntityManager.hpp"


namespace game {

    EntityManager::EntityManager()
    {
        _entities = std::make_shared<std::vector<std::shared_ptr<Entity>>>();
        std::random_device randomDevice;
        auto maxEntities = std::numeric_limits<std::uint32_t>::max();
        _generator = std::mt19937(randomDevice());
        _distribution = std::uniform_int_distribution<std::uint32_t>(0, maxEntities - 1);
    }

    std::shared_ptr<Entity> EntityManager::createEntity() {
        std::uint32_t entityId;
        std::shared_ptr<Entity> obj;

        if (!_availableEntities.empty()) {
            entityId = _availableEntities.front();
            _availableEntities.pop();
            obj = std::make_shared<Entity>(Entity(entityId));
            _entities->push_back(obj);
        } else {
            entityId = static_cast<std::uint32_t>(_distribution(_generator));
            obj = std::make_shared<Entity>(Entity(entityId));
            _entities->push_back(obj);
        }
        return obj;
    }

    void EntityManager::destroyEntity(const std::shared_ptr<std::vector<std::shared_ptr<Entity>>> &, std::uint32_t entityToDestroy) {
        for (size_t size = 0; size < _entities->size(); size++) {
            std::shared_ptr<Entity> &entity = _entities->at(size);
            if (entity->getId() == entityToDestroy) {
                _entities->erase(_entities->begin() + size);
                return;
            }
        }
    }

    std::shared_ptr<Entity> EntityManager::getEntity(std::uint32_t entityId) const {
        for (const auto &entity : *_entities) {
            if (entity->getId() == entityId) {
                return entity;
            }
        }
        return nullptr;
    }

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> EntityManager::getEntity() const {
        return _entities;
    }

    std::queue<std::uint32_t> EntityManager::getAvailableEntities() const {
        return _availableEntities;
    }

    std::shared_ptr<Entity> EntityManager::createPlayer(const pos &playerPos, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map) {
        std::shared_ptr<Entity> player = createEntity();

        player->addComponent<PositionComponent>(PositionComponent(playerPos.x, playerPos.y));
        player->addComponent<RenderableComponent>(RenderableComponent(SpriteType::PLAYER));
        player->addComponent<VelocityComponent>(VelocityComponent(2, 0));
        player->addComponent<RectableComponent>(RectableComponent(0));
        player->addComponent<ControllableComponent>(ControllableComponent(sf::Keyboard::Up,
                                                                          sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right));

        auto &sprite = player->getComponent<RenderableComponent>().getSprite();
        auto &con = player->getComponent<ControllableComponent>();
        con.setMap(map);
        player->getComponent<PositionComponent>().positionCallback([&sprite] (double x, double y) {
            sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
        });
        player->getComponent<PositionComponent>().setPos(playerPos.x, playerPos.y);

        return player;
    }

    std::shared_ptr<Entity> EntityManager::createWall(const pos &wallPos, sf::IntRect rect) {
        std::shared_ptr<Entity> wall = createEntity();

        wall->addComponent<PositionComponent>(PositionComponent(wallPos.x, wallPos.y));
        wall->addComponent<RenderableComponent>(RenderableComponent(SpriteType::MAP));
        wall->addComponent<WallsComponent>(WallsComponent());
        wall->addComponent<RectableComponent>(RectableComponent(rect));

        auto &sprite = wall->getComponent<RenderableComponent>().getSprite();
        sprite.setTextureRect(wall->getComponent<RectableComponent>().getRect());
        wall->getComponent<PositionComponent>().positionCallback([&sprite] (double x, double y) {
            sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
        });
        wall->getComponent<PositionComponent>().setPos(wallPos.x, wallPos.y);

        return wall;
    }

    std::shared_ptr<Entity> EntityManager::createPellet(const pos &pelletPos, sf::IntRect rect) {
        std::shared_ptr<Entity> pellet = createEntity();

        pellet->addComponent<PositionComponent>(PositionComponent(pelletPos.x, pelletPos.y));
        pellet->addComponent<RenderableComponent>(RenderableComponent(SpriteType::MAP));
        pellet->addComponent<RectableComponent>(RectableComponent(rect));
        pellet->addComponent<PelletsComponent>(PelletsComponent());

        auto &sprite = pellet->getComponent<RenderableComponent>().getSprite();
        sprite.setTextureRect(pellet->getComponent<RectableComponent>().getRect());
        pellet->getComponent<PositionComponent>().positionCallback([&sprite] (double x, double y) {
            sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
        });
        pellet->getComponent<PositionComponent>().setPos(pelletPos.x, pelletPos.y);

        return pellet;
    }

    std::shared_ptr<Entity> EntityManager::createEnergizer(const pos &energizerPos, sf::IntRect rect) {
        std::shared_ptr<Entity> energizer = createEntity();

        energizer->addComponent<PositionComponent>(PositionComponent(energizerPos.x, energizerPos.y));
        energizer->addComponent<RenderableComponent>(RenderableComponent(SpriteType::MAP));
        energizer->addComponent<RectableComponent>(RectableComponent(rect));
        energizer->addComponent<EnergizersComponent>(EnergizersComponent());

        auto &sprite = energizer->getComponent<RenderableComponent>().getSprite();
        sprite.setTextureRect(energizer->getComponent<RectableComponent>().getRect());
        energizer->getComponent<PositionComponent>().positionCallback([&sprite] (double x, double y) {
            sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
        });
        energizer->getComponent<PositionComponent>().setPos(energizerPos.x, energizerPos.y);

        return energizer;
    }

    std::shared_ptr<Entity> EntityManager::createDoor(const pos &doorPos, sf::IntRect rect) {
        std::shared_ptr<Entity> door = createEntity();

        door->addComponent<PositionComponent>(PositionComponent(doorPos.x, doorPos.y));
        door->addComponent<RenderableComponent>(RenderableComponent(SpriteType::MAP));
        door->addComponent<RectableComponent>(RectableComponent(rect));
        door->addComponent<DoorComponent>(DoorComponent());

        auto &sprite = door->getComponent<RenderableComponent>().getSprite();
        sprite.setTextureRect(door->getComponent<RectableComponent>().getRect());
        door->getComponent<PositionComponent>().positionCallback([&sprite] (double x, double y) {
            sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
        });
        door->getComponent<PositionComponent>().setPos(doorPos.x, doorPos.y);

        return door;
    }

}