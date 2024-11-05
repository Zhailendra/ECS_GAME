/*
** PROJECT, 2024
** CPP_POOL
** File description:
** GameSystem.cpp
*/

#include "GameSystem.hpp"

namespace game {

    GameSystem::GameSystem() {
        _currentWave = 0;
        _waveTimer = SCATTER_DURATION;
    }

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> GameSystem::getEntities()
    {
        return _entities;
    }

    void GameSystem::addEntity(std::shared_ptr<Entity> &entity)
    {
        _entities->push_back(entity);
    }

    void GameSystem::update(int gameLevel, bool resetGame) {
        if (resetGame) {
            reset(gameLevel);
        }
        for (auto &entity : *_entities) {
            if (entity->hasComponent<ControllableComponent>()) {
                auto &controllable = entity->getComponent<ControllableComponent>();
                if (controllable.getEnergyTimer() == 0) {
                    waveManager(gameLevel);
                }
            }
        }
    }

    void GameSystem::waveManager(int gameLevel) {
        if (_waveTimer == 0) {
            if (_currentWave < 7) {
                _currentWave++;
                for (auto &entity : *_entities) {
                    if (entity->hasComponent<GhostComponent>()) {
                        auto &ghost = entity->getComponent<GhostComponent>();
                        ghost.setScatter(1 - ghost.getScatter());
                    }
                }

                if ((_currentWave % 2) == 1) {
                    _waveTimer = CHASE_DURATION;
                } else if (_currentWave == 2) {
                    _waveTimer = static_cast<unsigned short>(SCATTER_DURATION / pow(2, gameLevel));
                } else {
                    _waveTimer = static_cast<unsigned short>(SCATTER_DURATION_BIS / pow(2, gameLevel));
                }
            }
        } else {
            _waveTimer--;
        }
    }

    void GameSystem::reset(int gameLevel) {
        _currentWave = 0;
        _waveTimer = static_cast<unsigned short>(SCATTER_DURATION / pow(2, gameLevel));
    }

}
