//
// Created by User on 7/3/2024.
//

#include "SceneGameOver.h"

SceneGameOver::SceneGameOver(GameEngine *gameEngine) : Scene(gameEngine) {
    init();
}

void SceneGameOver::init() {
    text.setFont(*gameEngine->getAssets().getFont("arial_bold"));

    text.setCharacterSize(90);
    text.setFillColor(sf::Color::Black);
    text.setString("GAME OVER\nPress Esc to go Exit");

    text.setPosition(static_cast<float>(gameEngine->getWindow().getSize().x) / 2 - text.getGlobalBounds().getSize().x / 2,
                     static_cast<float>(gameEngine->getWindow().getSize().y) / 2 - text.getGlobalBounds().getSize().y / 2);

    background.setTexture(*gameEngine->getAssets().getTexture("menu_background"));

    background.setScale(static_cast<float>(gameEngine->getWindow().getSize().x) /
                        static_cast<float>(background.getTexture()->getSize().x),
                        static_cast<float>(gameEngine->getWindow().getSize().y) /
                        static_cast<float>(background.getTexture()->getSize().y));
}

void SceneGameOver::update() {
    gameEngine->getWindow().draw(background);
    gameEngine->getWindow().draw(text);
}

void SceneGameOver::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            gameEngine->getWindow().close();
    }
}

