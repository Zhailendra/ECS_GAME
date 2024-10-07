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
#include "EntityManager.hpp"
#include "Renderable/RenderableComponent.hpp"
#include "Map.hpp"

namespace game {
    class Game {
        public:
            explicit Game(EntityManager &entityManager);
            ~Game();

            bool isRunning() const;
            bool pollEvent() { return _window.pollEvent(_event); }
            void closeWindow() { _window.close(); }
            void draw();

            void createMap(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &mapArray, bool isWallUp, bool isWallDown, bool isWallRight, bool isWallLeft);
            static void resetWalls(bool &isWallUp, bool &isWallDown, bool &isWallRight, bool &isWallLeft);
            void drawHitBox(const std::shared_ptr<Entity>& entity);

            sf::RenderWindow &getWindow() { return _window; }
            sf::Event &getEvent() { return _event; }
            sf::Clock &getClock() { return _clock; }
            float getDeltaTime() { return _clock.restart().asSeconds(); }

            void setDebugMode(bool mode) { _debugMode = mode; }
            bool &getDebugMode() { return _debugMode; }

        protected:
            bool _debugMode = false;
        private:
            sf::RenderWindow _window;
            sf::VideoMode _videoMode;
            sf::Event _event;
            sf::Clock _clock;

            EntityManager &_entityManager;
    };
}