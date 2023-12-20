#include "SceneStartMenu.h"
#include "ScenePlaying.h"

SceneStartMenu::SceneStartMenu(GameEngine* gameEngine): Scene(gameEngine) {
    init();
}

void SceneStartMenu::init() {
    background.setTexture(*gameEngine->getAssets().getTexture("menu_background"));
    background.setScale( static_cast<float>(gameEngine->getWindow().getSize().x) / static_cast<float>(background.getTexture()->getSize().x),
                         static_cast<float>(gameEngine->getWindow().getSize().y) / static_cast<float>(background.getTexture()->getSize().y));

    playRect = sf::RectangleShape(sf::Vector2f(384, 216));
    playRect.setPosition((static_cast<float>(gameEngine->getWindow().getSize().x) - playRect.getSize().x) / 2, 216);
    playRect.setFillColor(sf::Color(150, 0, 100));
    playRect.setOutlineColor(sf::Color::White);
    playRect.setOutlineThickness(4);

    quitRect = sf::RectangleShape(sf::Vector2f(384, 216));
    quitRect.setPosition((static_cast<float>(gameEngine->getWindow().getSize().x) - playRect.getSize().x) / 2, 648);
    quitRect.setFillColor(sf::Color(150, 0, 100));
    quitRect.setOutlineColor(sf::Color::Black);
    quitRect.setOutlineThickness(4);

    playText.setFont(*gameEngine->getAssets().getFont("arial_bold"));
    quitText.setFont(*gameEngine->getAssets().getFont("arial_bold"));

    playText.setString("Play");
    quitText.setString("Quit");

    playText.setCharacterSize(36);
    quitText.setCharacterSize(36);

    playText.setFillColor(sf::Color::Black);
    quitText.setFillColor(sf::Color::Black);

    auto gb1 = playRect.getGlobalBounds();
    auto gb2 = playText.getGlobalBounds();

    playText.setPosition(gb1.left + gb1.width / 2 - gb2.width / 2, gb1.top + gb1.height / 2 - gb2.height / 2);

    auto gb3 = quitRect.getGlobalBounds();
    auto gb4 = quitText.getGlobalBounds();

    quitText.setPosition(gb3.left + gb3.width / 2 - gb4.width / 2, gb3.top + gb3.height / 2 - gb4.height / 2);
}

void SceneStartMenu::update() {
    if (changedLastFrame) {
        if (indexSelected == 0) {
            playRect.setOutlineColor(sf::Color::White);
            quitRect.setOutlineColor(sf::Color::Black);
        } else {
            playRect.setOutlineColor(sf::Color::Black);
            quitRect.setOutlineColor(sf::Color::White);
        }
    }

    gameEngine->getWindow().draw(background);

    gameEngine->getWindow().draw(playRect);
    gameEngine->getWindow().draw(quitRect);

    gameEngine->getWindow().draw(playText);
    gameEngine->getWindow().draw(quitText);

    changedLastFrame = false;
}

void SceneStartMenu::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
            indexSelected--;
            changedLastFrame = true;
        }
        else if (event.key.code == sf::Keyboard::S) {
            indexSelected++;
            changedLastFrame = true;
        }
        if (indexSelected < 0)
            indexSelected = 1;
        if (indexSelected > 1)
            indexSelected = 0;

        if (event.key.code == sf::Keyboard::Enter) {
            if (indexSelected == 1)
                gameEngine->getWindow().close();
            else
                gameEngine->changeScene("Playing", std::make_shared<ScenePlaying>(gameEngine));
        }
    }
}
