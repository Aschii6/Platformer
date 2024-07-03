#pragma once

#include "../GameEngine.h"

class GameEngine;

class Scene {
protected:
    GameEngine* gameEngine;
public:
    explicit Scene(GameEngine* gameEngine): gameEngine(gameEngine) {}

    virtual void update() = 0;

    virtual void handleEvent(sf::Event& event) = 0;
};
