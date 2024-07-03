#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include "Animation.h"


class Assets {
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::map<std::string, std::shared_ptr<sf::Font>> fonts;
    std::map<std::string, std::shared_ptr<Animation>> animations;
public:
    void addTexture(const std::string &name, const std::string &filepath) {
        sf::Texture texture;
        if (!texture.loadFromFile(filepath))
            throw std::runtime_error("Couldn't load texture from file");
        textures.emplace(name, std::make_shared<sf::Texture>(texture));
    }

    void addFont(const std::string &name, const std::string &filepath) {
        sf::Font font;
        if (!font.loadFromFile(filepath))
            throw std::runtime_error("Couldn't load font from file");
        fonts.emplace(name, std::make_shared<sf::Font>(font));
    }

    void addAnimation(const std::string &name, const sf::Texture &texture, const sf::Vector2f &size,
                      const sf::Vector2f& scale, const int speed, const int frameCount) {
        animations.emplace(name, std::make_shared<Animation>(name, texture, size, speed, frameCount, scale));
    }

    std::shared_ptr<sf::Texture> getTexture(const std::string &name) {
        if (textures.find(name) == textures.end())
            throw std::runtime_error("Texture doesn't exist");
        return textures[name];
    }

    std::shared_ptr<sf::Font> getFont(const std::string &name) {
        if (fonts.find(name) == fonts.end())
            throw std::runtime_error("Font doesn't exist");
        return fonts[name];
    }

    std::shared_ptr<Animation> getAnimation(const std::string &name) {
        if (animations.find(name) == animations.end())
            throw std::runtime_error("Animation doesn't exist");
        return animations[name];
    }
};
