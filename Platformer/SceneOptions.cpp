#include "SceneOptions.h"

SceneOptions::SceneOptions(GameEngine *gameEngine): Scene(gameEngine) {
    init();
}

void SceneOptions::init() {
    text.setFont(*gameEngine->getAssets().getFont("arial_bold"));

    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Black);
    text.setString("WORK IN PROGRESS\nPress Esc to Exit\nPress Enter to go Back");

    text.setPosition(static_cast<float>(gameEngine->getWindow().getSize().x) / 2 - text.getGlobalBounds().getSize().x / 2,
                     static_cast<float>(gameEngine->getWindow().getSize().y) / 2 - text.getGlobalBounds().getSize().y / 2);

    background.setTexture(*gameEngine->getAssets().getTexture("menu_background"));
    background.setScale(static_cast<float>(gameEngine->getWindow().getSize().x) /
    static_cast<float>(background.getTexture()->getSize().x),
    static_cast<float>(gameEngine->getWindow().getSize().y) /
    static_cast<float>(background.getTexture()->getSize().y));
}

void SceneOptions::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            gameEngine->getWindow().close();
        else if (event.key.code == sf::Keyboard::Enter)
            gameEngine->changeScene("Playing", nullptr);
    }
}

void SceneOptions::update() {
    gameEngine->getWindow().draw(background);
    gameEngine->getWindow().draw(text);
}