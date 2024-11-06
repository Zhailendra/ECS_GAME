# Pacman ECS

Welcome to my **Pacman** project! This is a recreation of the classic Pacman game, implemented in C++ with an Entity-Component-System (ECS) architecture. This project aims to replicate Pacman while structuring the code in a modular, flexible way, enabling ease of extension and reuse of components.

## Table of Contents

- [Introduction](#introduction)
- [ECS Structure](#ecs-structure)
    - [Entity](#entity)
    - [Component](#component)
    - [System](#system)
- [Features](#features)
- [Requirements](#requirements)
- [Installation and Execution](#installation-and-execution)
- [Usage](#usage)
- [Contributing](#contributing)
- [Authors](#authors)

![Screenshot of the Pacman game](assets/)

## Introduction

This project recreates Pacman using an ECS structure to make the code modular. Every game element, from Pacman to ghosts and walls, is managed as entities composed of various components that represent specific attributes or abilities. The systems control the game logic by operating on these entities and components.

---

## ECS Structure

The ECS architecture is central to this project, divided into three main elements:

### Entity

An **Entity** represents a unique game object, like Pacman, a ghost, or a wall. Entities themselves do not contain behavior or specific attributes beyond their identification; they primarily serve as containers for the components they hold.

### Component

**Components** represent specific characteristics of an entity, such as:

- `PositionComponent`: contains an entity’s position data.
- `RenderableComponent`: holds graphic data like textures and sprites.
- `ControllableComponent`: manages player inputs for Pacman’s movement.
- `GhostComponent`: manages behaviors specific to ghosts, such as detecting Pacman.

By combining different components, each entity acquires the attributes needed to participate in the game’s mechanics.

### System

**Systems** encapsulate the logic that acts on groups of entities with certain components. In Pacman ECS, systems handle the game's updates each frame:

- `MovableSystem`: processes movement for Pacman and the ghosts.
- `HitBoxSystem`: checks collisions between Pacman, walls, ghosts, and pellets.
- `PlayerSystem`: manages Pacman’s interactions with the map.
- `GhostSystem`: controls the AI behavior for ghosts, including chase and evade states.

---

## Features

- **Pacman Movement**: Pacman can move freely in four directions.
- **Classic Game Mechanics**: pellets, ghosts, capture rules, and win/loss conditions are faithfully reproduced.
- **Ghost Behavior**: Ghosts follow specific behaviors (chasing, scattering) based on their position relative to Pacman.
- **Scoring System**: Score increases when Pacman eats all pellets on the map (Levels).
- **End Screen**: A victory screen appears when all pellets are eaten, and a defeat screen displays if Pacman is caught.

---

## Installation and Execution

1. **Clone the repository**:
    ```bash
    git clone https://github.com/Zhailendra/Pacman_ECS.git
    ```

2. **Compile the project**:
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```

3. **Run the game**:
    ```bash
    ./game
    ```
    
---

## Usage

- **Movement**: Use the arrow keys to move Pacman.
- **Restart**: If the game ends (win or loss), press `Enter` to restart.
- **Quit**: Press `Escape` to exit the game.

---

## Authors

- [Zhailendra](https://github.com/Zhailendra)

---

> **Note**: While using an ECS structure for a project like Pacman isn’t strictly necessary, I chose to implement it as a personal challenge. ECS allows for a highly modular codebase but can sometimes introduce minor performance lags, especially as systems scale with more entities.
So, if you’re looking to build a simple game like Pacman, you might not need to use ECS. However, if you’re interested in learning more about ECS and how it can be applied to game development, this project is a great starting point!