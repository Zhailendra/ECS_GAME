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
        _playerDeathCreated = false;
        _gameStopped = false;
        _isGameOver = false;
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
                auto &renderable = entity->getComponent<RenderableComponent>();
                if (!renderable.getDisplayable())
                    continue;
                sf::Sprite spriteToDisplay;
                spriteToDisplay = entity->getComponent<RenderableComponent>().getSprite();
                if (spriteToDisplay.getTexture() == nullptr)
                    continue;
                if (renderable.getDisplayBody()) {
                    _window.draw(spriteToDisplay);
                }
                if (entity->hasComponent<GhostComponent>()) {
                    sf::Sprite faceSprite = entity->getComponent<RenderableComponent>().getFace();
                    if (faceSprite.getTexture() == nullptr)
                        continue;
                    _window.draw(faceSprite);
                }
            }
        }

        for (const auto &entity : *_entityManager.getEntities()) {
            if (entity->hasComponent<TextComponent>()) {
                auto &text = entity->getComponent<TextComponent>();

                if (text.getDisplay() && text.getDisplayNow() && !_playerDeathCreated) {
                    _window.draw(text.getText());
                }
                if (text.getDisplay() && _gameStopped && displayText) {
                    _window.draw(text.getText());
                }

                if (_debugMode) {
                    drawHitBox(entity);
                    if (!text.getDisplay()) {
                        _window.draw(text.getText());
                    }
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
        _nbPelletsRemaining = _nbPellets;
    }

    void Game::resetWalls(bool &isWallUp, bool &isWallDown, bool &isWallRight, bool &isWallLeft) {
        isWallUp = false;
        isWallDown = false;
        isWallRight = false;
        isWallLeft = false;
    }

    void Game::drawHitBox(const std::shared_ptr<Entity>& entity) {
        if (entity->hasComponent<RenderableComponent>() && entity->hasComponent<ControllableComponent>()) {
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

    bool Game::resetGame(int &gameLevel, const pos &playerPos, const std::array<pos, 4> &ghostPos) {
        if (_playerDeathCreated && displayText) {
            std::cout << "Resetting game..." << std::endl;
            _nbPelletsRemaining = _nbPellets;
            _playerDeathCreated = false;
            _gameStopped = false;
            displayText = false;
            if (!_isGameOver) {
                gameLevel++;
                auto &text = _levelInfo->getComponent<TextComponent>();
                text.setStringText("LEVEL: " + std::to_string((gameLevel + 1)));
            } else {
                gameLevel = 0;
                auto &text = _levelInfo->getComponent<TextComponent>();
                text.setStringText("LEVEL: " + std::to_string((gameLevel + 1)));
                _isGameOver = false;
            }
            for (const auto &entity : *_entityManager.getEntities()) {
                if (entity->hasComponent<RenderableComponent>()) {
                    auto &renderable = entity->getComponent<RenderableComponent>();
                    if (renderable.getDisplayable() && renderable.getSpriteType() == PLAYER_DEATH) {
                        EntityManager::destroyEntity(_entityManager.getEntities(), entity->getId());
                        break;
                    }
                }
            }
            reDisplayEntities(playerPos, ghostPos);
            return true;
        }
        return false;
    }

    void Game::reDisplayEntities(const pos &playerPos, const std::array<pos, 4> &ghostPos) {
        for (const auto &entity : *_entityManager.getEntities()) {
            if (entity->hasComponent<RenderableComponent>()) {
                auto &renderable = entity->getComponent<RenderableComponent>();
                if (!renderable.getDisplayable()) {
                    renderable.setDisplayable(true);
                }
            }
            if (entity->hasComponent<GhostComponent>()) {
                auto &ghost = entity->getComponent<GhostComponent>();
                auto &renderable = entity->getComponent<RenderableComponent>();
                auto &sprite = renderable.getSprite();
                auto &face = renderable.getFace();
                auto &position = entity->getComponent<PositionComponent>();

                position.positionCallback([&sprite, &face](double x, double y) {
                    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
                    face.setPosition(static_cast<float>(x), static_cast<float>(y));
                });
                position.setPos(ghostPos[ghost.getGhostId()].x, ghostPos[ghost.getGhostId()].y);
            }
            if (entity->hasComponent<ControllableComponent>()) {
                auto &controllable = entity->getComponent<ControllableComponent>();
                auto &position = entity->getComponent<PositionComponent>();
                controllable.setIsPlaying(true);
                controllable.setIsDead(false);
                position.setPos(playerPos.x, playerPos.y);
            }
            if (entity->hasComponent<PelletsComponent>()) {
                auto &pellet = entity->getComponent<PelletsComponent>();
                if (pellet.getIsEaten()) {
                    pellet.setIsEaten(false);
                    pellet.setAlreadyConsumed(false);
                }
            } else if (entity->hasComponent<EnergizersComponent>()) {
                auto &energizer = entity->getComponent<EnergizersComponent>();
                if (energizer.getIsEaten()) {
                    energizer.setIsEaten(false);
                    energizer.setAlreadyConsumed(false);
                }
            }
        }
    }

    void Game::initPlayerDeath() {
        for (const auto &entity : *_entityManager.getEntities()) {
            if (entity->hasComponent<RenderableComponent>()) {
                auto &renderable = entity->getComponent<RenderableComponent>();
                renderable.setDisplayable(false);
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
        }
    }

    void Game::initInfo(int gameLevel) {
        std::string toDisplay = "\t\t\t\tYou won!\n\nPress Enter to play again\n\t\t\t\t\t  or\n\t\t  Escape to quit";
        sf::Vector2u windowSize = _window.getSize();
        double x = 50;
        double y = std::round(0.5f * double((OBJECT_SIZE * MAP_HEIGHT - FONT_SIZE * (1 + std::count(toDisplay.begin(), toDisplay.end(), '\n')))));

        pos fpsPos = {static_cast<double>(windowSize.x - 670), 10};
        pos nbEntitiesPos = {static_cast<double>(windowSize.x - 670), 30};
        pos messagePos = {x, y};
        pos levelPos = {static_cast<double>(windowSize.x - 670), 335};

        _fpsEntity = _entityManager.createText(fpsPos, "", sf::Color::White, 15, false, false, false);
        _nbEntities = _entityManager.createText(nbEntitiesPos, "", sf::Color::White, 15, false, false, false);
        _winMenu = _entityManager.createText(messagePos, toDisplay, sf::Color::White, 15, true, false, true);
        _levelInfo = _entityManager.createText(levelPos, "LEVEL: " + std::to_string(gameLevel + 1), sf::Color::White, 15, true, true, false);

        if (_fpsEntity && _nbEntities && _winMenu && _levelInfo) {
            _entityManager.getEntities()->push_back(_fpsEntity);
            _entityManager.getEntities()->push_back(_nbEntities);
            _entityManager.getEntities()->push_back(_winMenu);
            _entityManager.getEntities()->push_back(_levelInfo);
        } else {
            std::cerr << "Error: Unable to create text entities for FPS, entity count or win menu." << std::endl;
        }
    }

    void Game::checkGameState() {
        bool isGameOver = false;

        for (const auto &entity : *_entityManager.getEntities()) {
            if (entity->hasComponent<PelletsComponent>()) {
                auto &pellets = entity->getComponent<PelletsComponent>();

                if (pellets.getIsEaten() && !pellets.isAlreadyConsumed()) {
                    _nbPelletsRemaining--;
                    pellets.setAlreadyConsumed(true);
                }
            }
            if (entity->hasComponent<ControllableComponent>()) {
                auto &controllable = entity->getComponent<ControllableComponent>();
                isGameOver = controllable.getIsDead();
            }
        }

        if (_nbPelletsRemaining <= 0 && !_playerDeathCreated) {
            handleWin();
        } else if (isGameOver && !_playerDeathCreated) {
            handleGameOver();
        }
    }

    void Game::handleWin() {
        initPlayerDeath();
        _gameStopped = true;
        _winMenu->getComponent<TextComponent>().setStringText("\t\t\t\tYou won!\n\nPress Enter to play again\n\t\t\t\t\t  or\n\t\t  Escape to quit");
        std::cout << "Victoire ! Tous les pellets ont été mangés." << std::endl;
    }

    void Game::handleGameOver() {
        initPlayerDeath();
        _gameStopped = true;
        _isGameOver = true;
        _winMenu->getComponent<TextComponent>().setStringText("\t\t\t\tGame Over\n\nPress Enter to play again\n\t\t\t\t\t  or\n\t\t  Escape to quit");
        std::cout << "Défaite ! Le joueur est mort." << std::endl;
    }

}
