#pragma once

#include "Scene.h"

class SceneOptions: public Scene {
    sf::Sprite background;

    sf::Text text;

    void init();
public:
    explicit SceneOptions(GameEngine *gameEngine);

    void update() override;

    void handleEvent(sf::Event &event) override;
};
