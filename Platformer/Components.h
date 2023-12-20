#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"


class Component {
};

class CTransform: public Component {
public:
    sf::Vector2f pos;
    sf::Vector2f prevPos;
    sf::Vector2f velocity;

    sf::Vector2f maxVelocity{12.f, 20.f};

    CTransform() = default;

    CTransform(const sf::Vector2f pos, const sf::Vector2f velocity): pos(pos), prevPos(pos), velocity(velocity) {}

    CTransform(const sf::Vector2f pos, const sf::Vector2f velocity, const sf::Vector2f maxVelocity):
            pos(pos), prevPos(pos), velocity(velocity), maxVelocity(maxVelocity) {}
};

class CGravity: public Component {
public:
    float gravity = 0.55f;

    CGravity() = default;
};

class CDrag: public Component {
public:
    float drag = 0.9f;

    CDrag() = default;
};

class CBoundingBox: public Component {
public:
    sf::Vector2f size;
    sf::Vector2f halfSize;

    CBoundingBox() = default;

    explicit CBoundingBox(const sf::Vector2f& size): size(size) {
        halfSize = sf::Vector2f(size.x / 2, size.y / 2);
    }
};

class CSprite: public Component {
public:
    sf::Sprite sprite;

    explicit CSprite(const sf::Texture& t): sprite(t) {
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    }
};

class CAnimation: public Component {
public:
    Animation animation;

    explicit CAnimation(Animation animation): animation(std::move(animation)) {}

    void setAnimation(Animation anim) {
        this->animation = std::move(anim);
    }
};

class CState: public Component {
public:
    std::string state;

    explicit CState(std::string state): state(std::move(state)) {}
};

class CInput: public Component {
public:
    bool left{false}, right{false}, jump{false}, attack{false};
    bool canJump{false}, canAttack{true};

    CInput() = default;
};

class CHp: public Component {
public:
    int hp{0};
    int damageCd{0};

    CHp() = default;

    explicit CHp(int hp): hp(hp) {}
};

class CLifespan: public Component {
public:
    int lifespan{0};

    CLifespan() = default;

    explicit CLifespan(int lifespan): lifespan(lifespan) {}
};