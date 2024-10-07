/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Game.cpp
*/

#include "Game.hpp"

namespace game {

    Game::Game(EntityManager &entityManager) : _entityManager(entityManager)
    {
        _videoMode.width = OBJECT_SIZE * MAP_WIDTH * WINDOW_RESIZE;
        _videoMode.height = (FONT_SIZE + OBJECT_SIZE * MAP_HEIGHT) * WINDOW_RESIZE;
        _videoMode.bitsPerPixel = 32;
        _window.create(_videoMode, "Pacman", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
        _window.setView(sf::View(sf::FloatRect(0, 0, OBJECT_SIZE * MAP_WIDTH, FONT_SIZE + OBJECT_SIZE * MAP_HEIGHT)));
        _window.setFramerateLimit(60);
        _debugMode = false;
        _nbPellets = 0;
        _nbPelletsRemaining = 0;
        _nbEnergizers = 0;
    }

    Game::~Game() {}

    bool Game::isRunning() const {
        return _window.isOpen();
    }

    void Game::draw() {
        _window.clear();

        for (const auto &entity : *_entityManager.getEntity()) {
            if (entity->hasComponent<RenderableComponent>()) {
                sf::Sprite spriteToDisplay;
                spriteToDisplay = entity->getComponent<RenderableComponent>().getSprite();
                _window.draw(spriteToDisplay);
                if (_debugMode) {
                    drawHitBox(entity);
                }
            }
        }
        _window.display();
    }

    void Game::createMap(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &mapArray, bool isWallUp, bool isWallDown, bool isWallRight, bool isWallLeft) {
        for (unsigned char i = 0; i < MAP_WIDTH; i++) {
            for (unsigned char j = 0; j < MAP_HEIGHT; j++) {
                double x = i * OBJECT_SIZE;
                double y = j * OBJECT_SIZE;

                pos pos = {x, y};

                switch (mapArray[i][j]) {
                    case Cell::WALL:
                        resetWalls(isWallUp, isWallDown, isWallRight, isWallLeft);
                        (j < MAP_HEIGHT - 1) ? (Cell::WALL == mapArray[i][1 + j]) ? isWallDown = true : 0 : 0;
                        (0 < i) ? (Cell::WALL == mapArray[i - 1][j]) ? isWallLeft = true : 0 : isWallLeft = true;
                        (i < MAP_WIDTH - 1) ? (Cell::WALL == mapArray[1 + i][j]) ? isWallRight = true : 0 : isWallRight = true;
                        (0 < j) ? (Cell::WALL == mapArray[i][j - 1]) ? isWallUp = true : 0 : 0;
                        _entityManager.createWall(pos, sf::IntRect(OBJECT_SIZE * (isWallDown + 2 * (isWallLeft + 2 * (isWallRight + 2 * isWallUp))), 0, OBJECT_SIZE, OBJECT_SIZE));
                        break;
                    case Cell::PELLET:
                        _entityManager.createPellet(pos, sf::IntRect(0, OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
                        _nbPellets++;
                        break;
                    case Cell::ENERGIZER:
                        _entityManager.createEnergizer(pos, sf::IntRect(OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
                        _nbEnergizers++;
                        break;
                    case Cell::DOOR:
                        _entityManager.createDoor(pos, sf::IntRect(2 * OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE, OBJECT_SIZE));
                        break;
                    default:
                        break;
                }
            }
        }
    }

    void Game::resetWalls(bool &isWallUp, bool &isWallDown, bool &isWallRight, bool &isWallLeft) {
        isWallUp = false;
        isWallDown = false;
        isWallRight = false;
        isWallLeft = false;
    }

    void Game::drawHitBox(const std::shared_ptr<Entity>& entity) {
        if (!entity->hasComponent<RenderableComponent>() || !entity->hasComponent<ControllableComponent>())
            return;
        auto &renderable = entity->getComponent<RenderableComponent>();
        sf::RectangleShape border;
        border = sf::RectangleShape(sf::Vector2f(renderable.getSprite().getGlobalBounds().width, renderable.getSprite().getGlobalBounds().height));
        border.setPosition(renderable.getSprite().getPosition());
        border.setOutlineThickness(2);
        border.setOutlineColor(sf::Color::Red);
        border.setFillColor(sf::Color::Transparent);
        _window.draw(border);
    }

    void Game::resetGame() {

    }

    void Game::displayWinMenu() {
        std::cout << "You won !" << std::endl;
    }

    void Game::checkPellets() {
        int nbPellets = 0;
        for (const auto &entity : *_entityManager.getEntity()) {
            if (entity->hasComponent<PelletsComponent>()) {
                nbPellets < _nbPellets ? nbPellets++ : 0;
            }
        }

        _nbPelletsRemaining = nbPellets;
        if (_nbPelletsRemaining == 0) {
            displayWinMenu();
        }
    }

}
