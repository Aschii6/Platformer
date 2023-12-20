#pragma once

#include <random>
#include "Scene.h"
#include "EntityManager.h"

class ScenePlaying: public Scene {
    EntityManager entityManager;

    std::shared_ptr<Entity> player;

    sf::Sprite background;

    sf::Text text;

    sf::Color hitBoxColor{sf::Color::Red};
    sf::RectangleShape rect;

    int attackCd{0}, fireballCd{30};

    bool playerDead{false};

    std::mt19937 generator{std::random_device{}()};
    std::uniform_int_distribution<> intDistribution{0, 1};
    std::uniform_int_distribution<> posYDistribution{120, 840};

    void init();

    void spawnPlayer();

    void addTile(const std::string& textureName, const sf::Vector2f& gridPos);

    void sRender();
    void sMovement();
    void sInput();
    void sCollision();
    void sAnimation();
    void sAttack();
    void sLifespan();

    void handleFireballs();
public:
    explicit ScenePlaying(GameEngine* gameEngine);

    void update() override;

    void handleEvent(sf::Event &event) override;
};
