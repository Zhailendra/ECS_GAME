/*
** PROJECT, 2024
** Project
** File description:
** main.cpp
*/

#include <SFML/Window.hpp>

#include "Exception.hpp"
#include "Node.hpp"
#include "SpriteLoader.hpp"
#include "Game.hpp"
#include "EntityManager.hpp"
#include "Map.hpp"

#include "Game/GameSystem.hpp"
#include "Player/PlayerSystem.hpp"
#include "Movable/MovableSystem.hpp"
#include "Rectable/RectableSystem.hpp"
#include "Hitbox/HitboxSystem.hpp"
#include "Text/TextSystem.hpp"
#include "Ghost/GhostSystem.hpp"

int main()
{
    int gameLevel = 0;
    bool resetGame = false;
    game::SpriteLoader::loadAllTextures();
    game::Map map;
    map.initMap();
    game::EntityManager entityManager;
    game::Game game(entityManager);
    game.createMap(map.getMap(), map.isWallUp(), map.isWallDown(), map.isWallRight(), map.isWallLeft());
    game.initInfo(gameLevel);
    entityManager.createGhosts(map.getEnemiesPos());
    entityManager.createPlayer(map.getPlayerPos());

    std::shared_ptr<std::vector<sf::Event>> events = std::make_shared<std::vector<sf::Event>>();

    game::PlayerSystem playerSystem = game::PlayerSystem();
    game::GameSystem gameSystem = game::GameSystem();
    game::MovableSystem movableSystem = game::MovableSystem();
    game::RectableSystem rectableSystem = game::RectableSystem();
    game::HitboxSystem hitboxSystem = game::HitboxSystem();
    game::TextSystem textSystem = game::TextSystem();
    game::GhostSystem ghostSystem = game::GhostSystem();

    playerSystem.setInputs(events);
    ghostSystem.setInputs(events);

    playerSystem.setEntities(entityManager.getEntities());
    gameSystem.setEntities(entityManager.getEntities());
    movableSystem.setEntities(entityManager.getEntities());
    rectableSystem.setEntities(entityManager.getEntities());
    hitboxSystem.setEntities(entityManager.getEntities());
    textSystem.setEntities(entityManager.getEntities());
    ghostSystem.setEntities(entityManager.getEntities());

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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    resetGame = game.resetGame(gameLevel, map.getPlayerPos(), map.getEnemiesPos());
                    continue;
                }
                events->push_back(event);
            }
            game.checkGameState();
            gameSystem.update(gameLevel, resetGame);
            rectableSystem.update(gameLevel, resetGame);
            hitboxSystem.update(gameLevel, resetGame);
            playerSystem.update(gameLevel, resetGame);
            ghostSystem.update(gameLevel, resetGame);
            movableSystem.update(gameLevel, resetGame);
            textSystem.update(gameLevel, resetGame);
            game.draw();
        }
    } catch (const game::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}