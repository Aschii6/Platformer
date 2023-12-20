#pragma once

#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Scene.h"

class Scene;

class GameEngine {
    sf::RenderWindow window;

    Assets assets;
    std::map<std::string, std::shared_ptr<Scene>> scenes;
    std::string currentScene{};

    std::shared_ptr<Scene> getCurrentScene();

    void init();
    void update();
    void handleEvents();

    void loadAssets();
public:
    GameEngine();
    void run();

    void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene);
    sf::RenderWindow& getWindow();
    Assets& getAssets();
};
