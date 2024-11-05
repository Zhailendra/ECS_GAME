/*
** PROJECT, 2024
** CPP_POOL
** File description:
** GhostComponent.hpp
*/

#pragma once

#include <iostream>

#include "AComponent.hpp"
#include "Includes.hpp"

constexpr int GHOST_ANIMATION_SPEED = 4;
constexpr int GHOST_ANIMATION_FRAMES = 6;
constexpr int GHOST_FRIGHTENED_SPEED = 3;
constexpr int GHOST_ESCAPE_SPEED = 4;
constexpr int GHOST_1_CHASE = 2;
constexpr int GHOST_2_CHASE = 1;
constexpr int GHOST_3_CHASE = 4;

constexpr int CHASE_DURATION = 1024;
constexpr int ENERGIZER_DURATION = 512;
constexpr int FRAME_DURATION = 16667;
constexpr int GHOST_FLASH_START = 64;
constexpr int SCATTER_DURATION = 512;
constexpr int SCATTER_DURATION_BIS = 256;

namespace game {

    enum GhostMode {
        NORMAL = 0,
        FRIGHTENED = 1,
        ESCAPE = 2
    };

    class GhostComponent : public AComponent {
        public:
            GhostComponent();
            explicit GhostComponent(int ghostId, pos bluePos, pos redPos);
            ~GhostComponent() override = default;


            int getGhostId() const { return _ghostId; }
            int getAnimationTimer() const { return _animationTimer; }
            int getDirection() const { return _direction; }
            bool getScatter() const { return _scatter; }
            bool getUseDoor() const { return _useDoor; }
            pos getHomePosition() const { return _homePosition; }
            pos getHomeExitPosition() const { return _homeExitPosition; }
            int getTargetDirection() const { return _targetDirection; }
            pos getTargetPosition() const { return _targetPosition; }
            GhostMode getFrightenedMode() const { return _frightenedMode; }
            int getFrightenedSpeedTimer() const { return _frightenedSpeedTimer; }
            bool canMove() const { return _canMove; }

            void setDirection(int direction) { _direction = direction; }
            void setAnimationTimer(int animationTimer) { _animationTimer = animationTimer; }
            void setScatter(bool scatter) { _scatter = scatter; }
            void setUseDoor(bool useDoor) { _useDoor = useDoor; }
            void setHomePosition(pos homePosition) { _homePosition = homePosition; }
            void setHomeExitPosition(pos homeExitPosition) { _homeExitPosition = homeExitPosition; }
            void setTargetDirection(int targetDirection) { _targetDirection = targetDirection; }
            void setTargetPosition(pos targetPosition) { _targetPosition = targetPosition; }
            void setFrightenedMode(GhostMode frightenedMode) { _frightenedMode = frightenedMode; }
            void setFrightenedSpeedTimer(int frightenedSpeedTimer) { _frightenedSpeedTimer = frightenedSpeedTimer; }
            void setCanMove(bool canMove) { _canMove = canMove; }

        protected:
        private:
            int _ghostId;
            int _animationTimer;
            int _direction;
            GhostMode _frightenedMode;
            int _frightenedSpeedTimer;

            bool _scatter;
            bool _useDoor;
            bool _canMove;
            pos _homePosition;
            pos _homeExitPosition;

            int _targetDirection;
            pos _targetPosition;
    };

}