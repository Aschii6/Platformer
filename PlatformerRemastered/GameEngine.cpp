#include "GameEngine.h"
#include "scenes/SceneStartMenu.h"

GameEngine::GameEngine() {
    init();
}

void GameEngine::init() {
    window.create(sf::VideoMode::getDesktopMode(), "Platformer",
                  sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    loadAssets();

    changeScene("StartMenu", std::make_shared<SceneStartMenu>(this));
}

void GameEngine::run() {
    while (window.isOpen()) {
        update();
    }
}

void GameEngine::handleEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else
            getCurrentScene()->handleEvent(event);
    }
}

void GameEngine::update() {
    handleEvents();

    window.setView(window.getDefaultView());
    window.clear(sf::Color::Cyan);
    getCurrentScene()->update();
    window.display();
}

std::shared_ptr<Scene> GameEngine::getCurrentScene() {
    return scenes[currentScene];
}

void GameEngine::loadAssets() {
    assets.addTexture("background", "../Resources/background.png");
    assets.addTexture("menu_background", "../Resources/menu_bg.jpg");

    assets.addTexture("idle", "../Resources/idle.png");
    assets.addTexture("run", "../Resources/run.png");
    assets.addTexture("attack", "../Resources/attack.png");

    assets.addTexture("fireball", "../Resources/fireball.png");

    assets.addTexture("left", "../Resources/left.png");
    assets.addTexture("top_left", "../Resources/top_left.png");
    assets.addTexture("right", "../Resources/right.png");
    assets.addTexture("top_right", "../Resources/top_right.png");
    assets.addTexture("top", "../Resources/top.png");
    assets.addTexture("empty", "../Resources/empty.png");
    assets.addTexture("tile1", "../Resources/tile1.png");
    assets.addTexture("tile2", "../Resources/tile2.png");
    assets.addTexture("tile3", "../Resources/tile3.png");

    assets.addFont("arial_bold", "../Resources/arial_bold.ttf");

    assets.addAnimation("idle", *assets.getTexture("idle"), sf::Vector2f(22, 32),
                        sf::Vector2f(4, 4), 10, 6);
    assets.addAnimation("run", *assets.getTexture("run"), sf::Vector2f(25, 32),
                        sf::Vector2f(4, 4), 10, 8);
    assets.addAnimation("fireball", *assets.getTexture("fireball"), sf::Vector2f(302, 302),
                        sf::Vector2f(0.3, 0.3), 12, 5);
    assets.addAnimation("attack", *assets.getTexture("attack"), sf::Vector2f(43, 32),
                        sf::Vector2f(4, 4), 10, 4);
}

void GameEngine::changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene) {
    if (scenes.find(sceneName) == scenes.end())
        scenes[sceneName] = std::move(scene);
    currentScene = sceneName;}

sf::RenderWindow &GameEngine::getWindow() {
    return window;
}

Assets &GameEngine::getAssets() {
    return assets;
}
