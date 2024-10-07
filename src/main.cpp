/*
** PROJECT, 2024
** Project
** File description:
** main.cpp
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Exception.hpp"
#include "Node.hpp"
#include "SpriteLoader.hpp"
#include "Game.hpp"
#include "EntityManager.hpp"
#include "Map.hpp"

#include "Player/PlayerSystem.hpp"
#include "Movable/MovableSystem.hpp"
#include "Rectable/RectableSystem.hpp"
#include "Hitbox/HitboxSystem.hpp"

int main()
{
    game::SpriteLoader::loadAllTextures();
    game::Map map;
    map.initMap();
    game::EntityManager entityManager;
    game::Game game(entityManager);
    game.createMap(map.getMap(), map.isWallUp(), map.isWallDown(), map.isWallRight(), map.isWallLeft());
    entityManager.createPlayer(map.getPlayerPos(), map.getMap());

    std::shared_ptr<std::vector<sf::Event>> events = std::make_shared<std::vector<sf::Event>>();

    game::PlayerSystem playerSystem = game::PlayerSystem();
    game::MovableSystem movableSystem = game::MovableSystem();
    game::RectableSystem rectableSystem = game::RectableSystem();
    game::HitboxSystem hitboxSystem = game::HitboxSystem();

    playerSystem.setInputs(events);

    playerSystem.setEntities(entityManager.getEntity());
    movableSystem.setEntities(entityManager.getEntity());
    rectableSystem.setEntities(entityManager.getEntity());
    hitboxSystem.setEntities(entityManager.getEntity());

    try {
        while (game.isRunning()) {
            sf::Event &event = game.getEvent();
            events->clear();
            while (game.pollEvent()) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    game.closeWindow();
                    std::cout << "Closing window" << std::endl;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
                    game.setDebugMode(!game.getDebugMode());
                    continue;
                }
                events->push_back(event);
            }
            rectableSystem.update();
            hitboxSystem.update();
            playerSystem.update();
            movableSystem.update();
            game.draw();
        }
    } catch (const game::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}