#pragma once

#include <SFML/Graphics.hpp>


class Animation {
    std::string name;
    sf::Sprite sprite;
    int speed{0}, frameCount{0}, currentFrame{0}, switchCd{0};
    sf::Vector2f size;
    bool facingRight{true}, hasEnded{false};
public:
    Animation(std::string name, const sf::Texture& t, const sf::Vector2f& size, const int speed, const int frameCount,
              const sf::Vector2f& scale):
        name(std::move(name)), sprite(t), size(size), speed(speed), frameCount(frameCount)
        {
        sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(size.x),
                                          static_cast<int>(size.y)));

        sprite.setOrigin(size.x / 2, size.y / 2);
        sprite.scale(scale);
    }

    void update() {
        if (speed == 0) {
            return;
        }

        if (switchCd == speed) {
            switchCd = 0;
            currentFrame++;
            if (currentFrame == frameCount) {
                currentFrame = 0;
                hasEnded = true;
            }
            sprite.setTextureRect(sf::IntRect(currentFrame * static_cast<int>(size.x), 0,
                                              static_cast<int>(size.x),static_cast<int>(size.y)));
        }
        switchCd++;
    }

    void rotate() {
        sprite.setScale(-sprite.getScale().x, sprite.getScale().y);
        facingRight = !facingRight;
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

    std::string getName() {
        return name;
    }

    bool getFacingRight() const {
        return facingRight;
    }

    bool getHasEnded() const {
        return hasEnded;
    }
};
