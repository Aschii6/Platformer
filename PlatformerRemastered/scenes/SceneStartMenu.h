#pragma once

#include "Scene.h"
#include "../GameEngine.h"


class SceneStartMenu : public Scene {
    sf::Sprite background;

    sf::RectangleShape playRect, quitRect;

    sf::Text playText, quitText;

    short int indexSelected{0};

    bool changedLastFrame{false};

    void init();
public:
    explicit SceneStartMenu(GameEngine* gameEngine = nullptr);

    void update() override;

    void handleEvent(sf::Event& event) override;
};