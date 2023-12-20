#include "ScenePlaying.h"
#include "SceneOptions.h"

ScenePlaying::ScenePlaying(GameEngine *gameEngine) : Scene(gameEngine) {
    init();
}

void ScenePlaying::init() {
    background.setTexture(*gameEngine->getAssets().getTexture("background"));
    background.setScale(static_cast<float>(gameEngine->getWindow().getSize().x) /
                        static_cast<float>(background.getTexture()->getSize().x),
                        static_cast<float>(gameEngine->getWindow().getSize().y) /
                        static_cast<float>(background.getTexture()->getSize().y));

    spawnPlayer();

    for (int i = 0; i < 16; ++i) {
        std::string textureName = "tile" + std::to_string(i % 3 + 1);

        if ((i >= 1 && i <= 3) || (i >= 12 && i <= 14))
            textureName = "empty";

        addTile(textureName, sf::Vector2f(static_cast<float>(i), (1080.f / 120) - 1));
    }

    addTile("top_left", sf::Vector2f(12, 6));
    addTile("tile1", sf::Vector2f(13, 6));
    addTile("top_right", sf::Vector2f(14, 6));
    addTile("left", sf::Vector2f(12, 7));
    addTile("empty", sf::Vector2f(13, 7));
    addTile("right", sf::Vector2f(14, 7));

    addTile("top_left", sf::Vector2f(1, 6));
    addTile("tile2", sf::Vector2f(2, 6));
    addTile("top_right", sf::Vector2f(3, 6));
    addTile("left", sf::Vector2f(1, 7));
    addTile("empty", sf::Vector2f(2, 7));
    addTile("right", sf::Vector2f(3, 7));

    addTile("tile3", sf::Vector2f(7, 4));
    addTile("tile2", sf::Vector2f(8, 4));

    addTile("tile2", sf::Vector2f(1, 2));
    addTile("tile1", sf::Vector2f(2, 2));
    addTile("tile3", sf::Vector2f(3, 2));

    addTile("tile2", sf::Vector2f(12, 2));
    addTile("tile3", sf::Vector2f(13, 2));
    addTile("tile2", sf::Vector2f(14, 2));

    text.setFont(*gameEngine->getAssets().getFont("arial_bold"));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
}

void ScenePlaying::spawnPlayer() {
    auto entity = entityManager.addEntity("player");

    entity->addComponent<CTransform>(sf::Vector2f(150, 100), sf::Vector2f(0, 0));
    entity->addComponent<CBoundingBox>(sf::Vector2f(22 * 4, 32 * 4));

    entity->addComponent<CAnimation>(*gameEngine->getAssets().getAnimation("idle"));
    entity->addComponent<CInput>();
    entity->addComponent<CState>("idle");
    entity->addComponent<CGravity>();
    entity->addComponent<CDrag>();
    entity->addComponent<CHp>(100);

    player = entity;
}

void ScenePlaying::addTile(const std::string &textureName, const sf::Vector2f &gridPos) {
    auto entity = entityManager.addEntity("tile");

    sf::Vector2f pos(gridPos.x * 120 + 60, gridPos.y * 120 + 60);

    entity->addComponent<CTransform>(pos, sf::Vector2f(0, 0));
    entity->addComponent<CBoundingBox>(sf::Vector2f(120, 120));

    entity->addComponent<CSprite>(*gameEngine->getAssets().getTexture(textureName));
    /*entity->getComponent<CSprite>().sprite.
            scale(120.f / static_cast<float>(entity->getComponent<CSprite>().sprite.getTexture()->getSize().x),
                  120.f / static_cast<float>(entity->getComponent<CSprite>().sprite.getTexture()->getSize().y));*/
    entity->getComponent<CSprite>().sprite.scale(5, 5);
    entity->getComponent<CSprite>().sprite.setPosition(pos);
}

void ScenePlaying::update() {
    handleFireballs();

    sInput();
    sMovement();
    sCollision();
    sAnimation();
    sAttack();
    sLifespan();
    entityManager.update();
    sRender();
}

void ScenePlaying::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            gameEngine->changeScene("Options", std::make_shared<SceneOptions>(gameEngine));
        else if (player->hasComponent<CInput>()) {
            if (event.key.code == sf::Keyboard::A)
                player->getComponent<CInput>().left = true;
            else if (event.key.code == sf::Keyboard::D)
                player->getComponent<CInput>().right = true;
            else if (event.key.code == sf::Keyboard::Space)
                if (player->getComponent<CInput>().canJump)
                    player->getComponent<CInput>().jump = true;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (player->hasComponent<CInput>()) {
            if (event.key.code == sf::Keyboard::A)
                player->getComponent<CInput>().left = false;
            else if (event.key.code == sf::Keyboard::D)
                player->getComponent<CInput>().right = false;
        }
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left)
            if (player->getComponent<CInput>().canAttack)
                player->getComponent<CInput>().attack = true;
    }
}

void ScenePlaying::sRender() {
    gameEngine->getWindow().draw(background);
    for (auto &entity: entityManager.getEntities()) {
        if (entity->hasComponent<CAnimation>()) {
            gameEngine->getWindow().draw(entity->getComponent<CAnimation>().animation.getSprite());
        } else if (entity->hasComponent<CSprite>()) {
            gameEngine->getWindow().draw(entity->getComponent<CSprite>().sprite);
        }

        /*if (entity->getTag() == "player" && entity->hasComponent<CBoundingBox>() && entity->hasComponent<CTransform>()) {
            auto& boundingBox = entity->getComponent<CBoundingBox>();
            sf::RectangleShape hRect;
            hRect.setPosition(entity->getComponent<CTransform>().pos - boundingBox.halfSize);
            hRect.setSize(boundingBox.size);
            hRect.setFillColor(sf::Color::Transparent);
            hRect.setOutlineColor(hitBoxColor);
            hRect.setOutlineThickness(2);
            gameEngine->getWindow().draw(hRect);
        }*/
    }

    /*if (attackCd > 30 && attackCd <= 40) {
        gameEngine->getWindow().draw(rect);
    }*/

    if (!player->hasComponent<CHp>())
        return;

    text.setPosition(10, 10);
    text.setString("HP: " + std::to_string(player->getComponent<CHp>().hp));
    gameEngine->getWindow().draw(text);
}

void ScenePlaying::sMovement() {
    for (const auto &entity: entityManager.getEntities()) {
        if (entity->hasComponent<CTransform>() && entity->hasComponent<CBoundingBox>()) {
            auto &transform = entity->getComponent<CTransform>();
            auto &boundingBox = entity->getComponent<CBoundingBox>();

            if (entity->hasComponent<CDrag>()) {
                transform.velocity.x *= entity->getComponent<CDrag>().drag;

                if (std::abs(transform.velocity.x) < 0.4f)
                    transform.velocity.x = 0;
            }

            if (entity->hasComponent<CGravity>())
                transform.velocity.y += entity->getComponent<CGravity>().gravity;

            if (std::abs(transform.velocity.x) > transform.maxVelocity.x) {
                transform.velocity.x =
                        transform.maxVelocity.x * (transform.velocity.x / std::abs(transform.velocity.x));
            }
            if (std::abs(transform.velocity.y) > transform.maxVelocity.y) {
                transform.velocity.y =
                        transform.maxVelocity.y * (transform.velocity.y / std::abs(transform.velocity.y));
            }

            transform.prevPos = transform.pos;
            transform.pos += transform.velocity;

            if (entity->getTag() == "player") {
                if (transform.pos.x - boundingBox.halfSize.x < 0) {
                    transform.pos.x = boundingBox.halfSize.x;
                    transform.velocity.x = 0.f;
                } else if (transform.pos.x + boundingBox.halfSize.x >
                           static_cast<float>(gameEngine->getWindow().getSize().x)) {
                    transform.pos.x = static_cast<float>(gameEngine->getWindow().getSize().x) - boundingBox.halfSize.x;
                    transform.velocity.x = 0.f;
                }

                if (transform.pos.y - boundingBox.halfSize.y < 0) {
                    transform.pos.y = boundingBox.halfSize.y;
                    transform.velocity.y = 0;
                }
            }

            // repeatedly setting pos for tiles so maybe comment
            if (entity->hasComponent<CSprite>())
                entity->getComponent<CSprite>().sprite.setPosition(transform.pos);
            else if (entity->hasComponent<CAnimation>())
                entity->getComponent<CAnimation>().animation.getSprite().setPosition(transform.pos);
        }
    }
}

void ScenePlaying::sInput() {
    if (player->hasComponent<CInput>()) {
        auto &input = player->getComponent<CInput>();
        auto &transform = player->getComponent<CTransform>();

        if (attackCd == 0)
            input.canAttack = true;

        if (input.left) {
            if (transform.velocity.x > 0)
                transform.velocity.x = 0.f;
            transform.velocity.x -= 1.5f;
        } else if (input.right) {
            if (transform.velocity.x < 0)
                transform.velocity.x = 0.f;
            transform.velocity.x += 1.5f;
        }
        if (input.jump) {
            transform.velocity.y = -transform.maxVelocity.y;
            input.jump = false;
            input.canJump = false;
        }
        if (input.attack) {
            attackCd = 60;
            input.attack = false;
            input.canAttack = false;
        }
    }
}

void ScenePlaying::sCollision() {
    hitBoxColor = sf::Color::Red;
    if (!player->hasComponent<CBoundingBox>() || !player->hasComponent<CTransform>())
        return;
    auto &playerTransform = player->getComponent<CTransform>();
    auto &playerBoundingBox = player->getComponent<CBoundingBox>();

    sf::FloatRect playerRect(playerTransform.pos - playerBoundingBox.halfSize, playerBoundingBox.size);

    for (const auto &entity: entityManager.getEntities("tile")) {
        if (!entity->hasComponent<CBoundingBox>() || !entity->hasComponent<CTransform>())
            continue;

        auto &tileTransform = entity->getComponent<CTransform>();
        auto &tileBoundingBox = entity->getComponent<CBoundingBox>();

        sf::FloatRect tileRect(tileTransform.pos - tileBoundingBox.halfSize, tileBoundingBox.size);

        sf::FloatRect intersection; // scraped using this

        if (!playerRect.intersects(tileRect, intersection))
            continue;

        // maybe a small offset, seems to be working now so idk
        if (intersection.height < intersection.width) {
            hitBoxColor = sf::Color::Green;
            if (playerTransform.pos.y + playerBoundingBox.halfSize.y > tileTransform.pos.y - tileBoundingBox.halfSize.y)
                if (playerTransform.prevPos.y + playerBoundingBox.halfSize.y <= tileTransform.pos.y - tileBoundingBox.halfSize.y) {
                    playerTransform.pos.y = tileTransform.pos.y - tileBoundingBox.halfSize.y - playerBoundingBox.halfSize.y;
                    playerTransform.velocity.y = 0.f;
                    player->getComponent<CInput>().canJump = true;
                }

            if (playerTransform.pos.y - playerBoundingBox.halfSize.y < tileTransform.pos.y + tileBoundingBox.halfSize.y)
                if (playerTransform.prevPos.y - playerBoundingBox.halfSize.y >= tileTransform.pos.y + tileBoundingBox.halfSize.y) {
                    playerTransform.pos.y = tileTransform.pos.y + tileBoundingBox.halfSize.y + playerBoundingBox.halfSize.y;
                    playerTransform.velocity.y = 0.f;
                }
        } else {
            hitBoxColor = sf::Color::Blue;
            if (playerTransform.pos.x + playerBoundingBox.halfSize.x > tileTransform.pos.x - tileBoundingBox.halfSize.x)
                if (playerTransform.prevPos.x + playerBoundingBox.halfSize.x <= tileTransform.pos.x - tileBoundingBox.halfSize.x) {
                    playerTransform.pos.x = tileTransform.pos.x - tileBoundingBox.halfSize.x - playerBoundingBox.halfSize.x;
                    playerTransform.velocity.x = 0.01f;
                }

            if (playerTransform.pos.x - playerBoundingBox.halfSize.x < tileTransform.pos.x + tileBoundingBox.halfSize.x)
                if (playerTransform.prevPos.x - playerBoundingBox.halfSize.x >= tileTransform.pos.x + tileBoundingBox.halfSize.x) {
                    playerTransform.pos.x = tileTransform.pos.x + tileBoundingBox.halfSize.x + playerBoundingBox.halfSize.x;
                    playerTransform.velocity.x = -0.01f;
                }
        }
    }

    auto& hp = player->getComponent<CHp>();
    if (hp.damageCd > 0)
        hp.damageCd--;

    if (hp.damageCd > 0)
        return;

    for (const auto& fireball : entityManager.getEntities("fireball")) {
        if (!fireball->hasComponent<CBoundingBox>() || !fireball->hasComponent<CTransform>())
            continue;

        auto &fireballTransform = fireball->getComponent<CTransform>();
        auto &fireballBoundingBox = fireball->getComponent<CBoundingBox>();

        sf::FloatRect fireballRect(fireballTransform.pos - fireballBoundingBox.halfSize, fireballBoundingBox.size);

        if (fireballRect.intersects(playerRect)) {
            hp.hp -= 10;
            hp.damageCd = 30;
            if (hp.hp <= 0) {
                playerDead = true;

                /*gameEngine->changeScene("GameOver", std::make_shared<SceneGameOver>(gameEngine));*/
            }
            break;
        }
    }
}

void ScenePlaying::sAnimation() {
    for (const auto &entity: entityManager.getEntities()) {
        if (entity->hasComponent<CAnimation>()) {
            entity->getComponent<CAnimation>().animation.update();

            if (entity->hasComponent<CTransform>()) {
                auto &transform = entity->getComponent<CTransform>();

                if (transform.velocity.x != 0) {
                    bool facingRight = true;
                    if (transform.velocity.x < 0)
                        facingRight = false;

                    if (entity->getComponent<CAnimation>().animation.getFacingRight() != facingRight)
                        entity->getComponent<CAnimation>().animation.rotate();
                }

                if (entity->getTag() == "player" && entity->hasComponent<CState>()) {
                    auto &state = entity->getComponent<CState>();

                    if (attackCd > 20 && attackCd <= 60) {
                        if (state.state != "attack") {
                            state.state = "attack";
                            entity->getComponent<CAnimation>().setAnimation(*gameEngine->getAssets().getAnimation("attack"));
                            entity->getComponent<CAnimation>().animation.getSprite().setPosition(transform.pos);
                        }
                        return;
                    }

                    if (std::abs(transform.velocity.y) < 0.56f) {
                        if (transform.velocity.x == 0) {
                            if (state.state != "idle") {
                                // this doesn't fix it xdd
                                bool toRotate = !entity->getComponent<CAnimation>().animation.getFacingRight();
                                state.state = "idle";
                                entity->getComponent<CAnimation>().setAnimation(
                                        *gameEngine->getAssets().getAnimation("idle"));
                                entity->getComponent<CAnimation>().animation.getSprite().setPosition(transform.pos);

                                if (toRotate)
                                    entity->getComponent<CAnimation>().animation.rotate();

                                entity->getComponent<CBoundingBox>().size = sf::Vector2f(22 * 4, 32 * 4);
                                entity->getComponent<CBoundingBox>().halfSize = sf::Vector2f(22 * 2, 32 * 2);
                            }
                        } else {
                            if (state.state != "run") {
                                state.state = "run";
                                entity->getComponent<CAnimation>().setAnimation(
                                        *gameEngine->getAssets().getAnimation("run"));
                                entity->getComponent<CAnimation>().animation.getSprite().setPosition(transform.pos);
                                /*entity->getComponent<CBoundingBox>().size = sf::Vector2f(25 * 4, 32 * 4);
                                entity->getComponent<CBoundingBox>().halfSize = sf::Vector2f(25 * 2, 32 * 2);*/
                            }
                        }
                    }
                }
            }
        }
    }
}

void ScenePlaying::sAttack() {
    if (attackCd > 0)
        attackCd--;

    if (!player->hasComponent<CTransform>())
        return;
    auto& playerTransform = player->getComponent<CTransform>();
    auto& playerBoundingBox = player->getComponent<CBoundingBox>();

    if (!(attackCd > 30 && attackCd <= 40))
        return;

    bool facingRight = player->getComponent<CAnimation>().animation.getFacingRight();

    sf::FloatRect attackRect(playerTransform.pos.x, playerTransform.pos.y - playerBoundingBox.halfSize.y,
                             playerBoundingBox.size.x + 25,playerBoundingBox.size.y);

    if (!facingRight)
        attackRect.left -= (playerBoundingBox.size.x + 25 * 2);

    rect.setSize(attackRect.getSize());
    rect.setPosition(attackRect.getPosition());

    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(2);
    rect.setFillColor(sf::Color::Transparent);

    for (const auto& entity: entityManager.getEntities("fireball")) {
        if (!entity->hasComponent<CHp>() || !entity->hasComponent<CTransform>() || !entity->hasComponent<CBoundingBox>())
            return;

        auto &transform = entity->getComponent<CTransform>();
        auto &boundingBox = entity->getComponent<CBoundingBox>();

        sf::FloatRect fireballRect(transform.pos - boundingBox.halfSize, boundingBox.size);


        if (attackRect.intersects(fireballRect)) {
            auto& hp = entity->getComponent<CHp>();
            hp.hp -= 20;
            if (hp.hp <= 0)
                entity->destroy();
        }
    }
}

void ScenePlaying::handleFireballs() {
    if (fireballCd > 0)
        fireballCd--;

    if (fireballCd == 0) {
        fireballCd = 60;

        auto entity = entityManager.addEntity("fireball");

        int c = intDistribution(generator);

        if (c == 0) {
            entity->addComponent<CTransform>(sf::Vector2f(0, static_cast<float>(posYDistribution(generator))),
                                             sf::Vector2f(10, 0));
        } else {
            entity->addComponent<CTransform>(sf::Vector2f(1920, static_cast<float>(posYDistribution(generator))),
                                             sf::Vector2f(-10, 0));
        }

        entity->addComponent<CBoundingBox>(sf::Vector2f(100, 100));
        entity->addComponent<CAnimation>(*gameEngine->getAssets().getAnimation("fireball"));
        entity->getComponent<CAnimation>().animation.getSprite().setPosition(entity->getComponent<CTransform>().pos);

        entity->addComponent<CHp>(15);

        entity->addComponent<CLifespan>(420);
    }
}

void ScenePlaying::sLifespan() {
    for (const auto& entity : entityManager.getEntities()) {
        if (!entity->hasComponent<CLifespan>())
            return;

        entity->getComponent<CLifespan>().lifespan--;

        if (entity->getComponent<CLifespan>().lifespan < 0)
            entity->destroy();
    }
}
