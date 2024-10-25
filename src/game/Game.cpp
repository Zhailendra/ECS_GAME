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
        _level = 1;
        _nbPellets = 0;
        _nbPelletsRemaining = 0;
        _nbEnergizers = 0;
        _playerDeathCreated = false;
        _winMenuCreated = false;
    }

    Game::~Game() {}

    bool Game::isRunning() {
        if (int((_fpsClock.getElapsedTime().asSeconds() * 100) / 10) % 3 == 0) {
            _end_point_fps = std::chrono::high_resolution_clock::now();
            _fps = std::round((float) 1e9 /
                              (float) std::chrono::duration_cast<std::chrono::nanoseconds>(
                                      _end_point_fps - _start_point_fps).count());
            _fpsEntity->getComponent<TextComponent>().setStringText("FPS: " + std::to_string(int(_fps)));
            _nbEntities->getComponent<TextComponent>().setStringText("ENTITIES: " + std::to_string(_entityManager.getSize()));
        }
        if (int((_fpsClock.getElapsedTime().asSeconds() * 100) / 10) % 3 == 0) {
            _start_point_fps = std::chrono::high_resolution_clock::now();
        }
        return _window.isOpen();
    }

    void Game::draw() {
        _window.clear();

        for (const auto &entity : *_entityManager.getEntities()) {
            if (entity->hasComponent<RenderableComponent>()) {
                sf::Sprite spriteToDisplay;
                spriteToDisplay = entity->getComponent<RenderableComponent>().getSprite();
                if (spriteToDisplay.getTexture() == nullptr)
                    continue;
                _window.draw(spriteToDisplay);
                if (entity->hasComponent<GhostComponent>()) {
                    sf::Sprite faceSprite = entity->getComponent<RenderableComponent>().getFace();
                    if (faceSprite.getTexture() == nullptr)
                        continue;
                    _window.draw(faceSprite);
                }
            }
        }

        for (const auto &entity : *_entityManager.getEntities()) {
            if (_debugMode) {
                drawHitBox(entity);
            }
            if (entity->hasComponent<TextComponent>()) {
                auto &text = entity->getComponent<TextComponent>();
                if ((text.getDisplay() && text.getDisplayNow() && !_playerDeathCreated) ||
                    (_winMenuCreated && text.getDisplay()) ||
                    (_debugMode && !text.getDisplay())) {
                    _window.draw(text.getText());
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
        if (entity->hasComponent<RenderableComponent>() && entity->hasComponent<ControllableComponent>() && !_winMenuCreated) {
            auto &renderable = entity->getComponent<RenderableComponent>();
            sf::RectangleShape border;
            border = sf::RectangleShape(sf::Vector2f(renderable.getSprite().getGlobalBounds().width,
                                                     renderable.getSprite().getGlobalBounds().height));
            border.setPosition(renderable.getSprite().getPosition());
            border.setOutlineThickness(2);
            border.setOutlineColor(sf::Color::Red);
            border.setFillColor(sf::Color::Transparent);
            _window.draw(border);
        }
        if (entity->hasComponent<TextComponent>()) {
            sf::RectangleShape border;
            auto &text = entity->getComponent<TextComponent>();
            if (!text.getDisplay()) {
                border = sf::RectangleShape(sf::Vector2f(text.getText().getGlobalBounds().width + 2,
                                                         text.getText().getGlobalBounds().height + 2));
                border.setPosition(text.getText().getPosition());
                border.setFillColor(sf::Color::Black);
                _window.draw(border);
            }
        }
    }

    void Game::resetGame(Map map) {
        if (_winMenuCreated) {
            _nbPellets = 0;
            _nbPelletsRemaining = 0;
            _nbEnergizers = 0;
            _playerDeathCreated = false;
            _winMenuCreated = false;
            displayWinText = false;
            _level++;
            auto &text = _levelInfo->getComponent<TextComponent>();
            text.setStringText("LEVEL: " + std::to_string(_level));
            _entityManager.clearEntities();
            createMap(map.getMap(), map.isWallUp(), map.isWallDown(), map.isWallRight(), map.isWallLeft());
            _entityManager.createPlayer(map.getPlayerPos());
        }
    }

    void Game::displayWinMenu() {
        std::vector<std::shared_ptr<Entity>> toRemove;

        for (const auto &entity : *_entityManager.getEntities()) {
            if (entity->hasComponent<TextComponent>()) {
                continue;
            }
            if (entity->hasComponent<RenderableComponent>() &&
                entity->hasComponent<ControllableComponent>() &&
                entity->hasComponent<PositionComponent>()) {

                auto &controllable = entity->getComponent<ControllableComponent>();
                auto &position = entity->getComponent<PositionComponent>();

                controllable.setIsPlaying(false);
                if (_entityManager.createPlayerDeath(position.getPos())) {
                    _playerDeathCreated = true;
                }
            }
            toRemove.push_back(entity);
        }

        for (const auto &entity : toRemove) {
            if (entity->hasComponent<RenderableComponent>()) {
                EntityManager::destroyEntity(_entityManager.getEntities(), entity->getId());
            }
        }
    }

    void Game::initInfo() {
        std::string toDisplay = "\t\t\t\tYou won!\n\nPress Enter to play again\n\t\t\t\t\t  or\n\t\t  Escape to quit";
        sf::Vector2u windowSize = _window.getSize();
        double x = 50;
        double y = std::round(0.5f * double((OBJECT_SIZE * MAP_HEIGHT - FONT_SIZE * (1 + std::count(toDisplay.begin(), toDisplay.end(), '\n')))));

        pos fpsPos = {static_cast<double>(windowSize.x - 670), 10};
        pos nbEntitiesPos = {static_cast<double>(windowSize.x - 670), 30};
        pos messagePos = {x, y};
        pos levelPos = {static_cast<double>(windowSize.x - 670), 335};

        _fpsEntity = _entityManager.createText(fpsPos, "", sf::Color::White, 15, false, false);
        _nbEntities = _entityManager.createText(nbEntitiesPos, "", sf::Color::White, 15, false, false);
        _winMenu = _entityManager.createText(messagePos, toDisplay, sf::Color::White, 15, true, false);
        _levelInfo = _entityManager.createText(levelPos, "LEVEL: " + std::to_string(_level), sf::Color::White, 15, true, true);

        if (_fpsEntity && _nbEntities && _winMenu && _levelInfo) {
            _entityManager.getEntities()->push_back(_fpsEntity);
            _entityManager.getEntities()->push_back(_nbEntities);
            _entityManager.getEntities()->push_back(_winMenu);
            _entityManager.getEntities()->push_back(_levelInfo);
        } else {
            std::cerr << "Error: Unable to create text entities for FPS, entity count or win menu." << std::endl;
        }
    }

    void Game::checkPellets() {
        int nbPellets = 0;
        for (const auto &entity : *_entityManager.getEntities()) {
            if (entity->hasComponent<PelletsComponent>()) {
                nbPellets++;
            }
        }

        _nbPelletsRemaining = nbPellets;
        if (_nbPelletsRemaining == 0 && !_winMenuCreated) {
            if (!_playerDeathCreated) {
                displayWinMenu();
            }
            if (displayWinText) {
                _winMenuCreated = true;
            }
        }
    }

}
