#pragma once

#include "Scene.h"

class SceneGameOver: public Scene {
    sf::Sprite background;

    sf::Text text;

    void init();
public:
    explicit SceneGameOver(GameEngine *gameEngine);

    void update() override;

    void handleEvent(sf::Event &event) override;
};

