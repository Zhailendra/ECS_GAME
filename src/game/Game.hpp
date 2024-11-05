/*
** PROJECT, 2024
** CPP_POOL
** File description:
** Game.hpp
*/

#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>

#include "EntityManager.hpp"
#include "Renderable/RenderableComponent.hpp"
#include "Map.hpp"

namespace game {

    class Game {
        public:
            explicit Game(EntityManager &entityManager);
            ~Game();

            bool isRunning();
            bool pollEvent() { return _window.pollEvent(_event); }
            void closeWindow() { _window.close(); }
            void draw();

            void createMap(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &mapArray, bool isWallUp, bool isWallDown, bool isWallRight, bool isWallLeft);
            static void resetWalls(bool &isWallUp, bool &isWallDown, bool &isWallRight, bool &isWallLeft);
            void drawHitBox(const std::shared_ptr<Entity>& entity);


            void checkGameState();
            void handleWin();
            void handleGameOver();

            bool resetGame(int &gameLevel, const pos &playerPos, const std::array<pos, 4> &ghostPos);
            void reDisplayEntities(const pos &playerPos, const std::array<pos, 4> &ghostPos);

            void initPlayerDeath();

            void initInfo(int gameLevel);

            sf::RenderWindow &getWindow() { return _window; }
            sf::Event &getEvent() { return _event; }
            sf::Clock &getClock() { return _clock; }
            float getDeltaTime() { return _clock.restart().asSeconds(); }

            void setDebugMode(bool mode) { _debugMode = mode; }
            bool &getDebugMode() { return _debugMode; }

        protected:
            bool _debugMode = false;
            std::shared_ptr<Entity> _fpsEntity;
            std::shared_ptr<Entity> _nbEntities;
            std::shared_ptr<Entity> _winMenu;
            std::shared_ptr<Entity> _levelInfo;
        private:
            sf::RenderWindow _window;
            sf::VideoMode _videoMode;
            sf::Event _event;
            sf::Clock _clock;

            int _nbPellets;
            int _nbPelletsRemaining;
            int _nbEnergizers;

            EntityManager &_entityManager;

            sf::Clock _fpsClock;
            std::chrono::high_resolution_clock::time_point _start_point_fps;
            std::chrono::high_resolution_clock::time_point _end_point_fps;
            float _fps;

            bool _playerDeathCreated;
            bool _gameStopped;
            bool _isGameOver;
    };

}