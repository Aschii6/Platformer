#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Components.h"


class Entity {
    friend class EntityManager;

    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
    std::string tag = "default";
    bool alive = true;
    unsigned long id = 0;

    Entity(const unsigned long id, std::string tag): id(id), tag(std::move(tag)) {}
public:
    template <typename ComponentType, typename... Args>
    void addComponent(Args&&... args) {
        if (!hasComponent<ComponentType>())
            components[typeid(ComponentType)] = std::make_shared<ComponentType>(std::forward<Args>(args)...);
    }

    template <typename ComponentType>
    bool hasComponent() const {
        return components.find(typeid(ComponentType)) != components.end();
    }

    template <typename ComponentType>
    ComponentType& getComponent() {
        try {
            const auto& componentPtr = components.at(typeid(ComponentType));
            return *std::static_pointer_cast<ComponentType>(componentPtr);
        } catch (const std::out_of_range&) {
            throw std::out_of_range("Component not found in entity.");
        } catch (const std::bad_cast&) {
            throw std::bad_cast();
        }
    }

    template <typename ComponentType>
    void removeComponent() {
        if (const auto it = components.find(typeid(ComponentType)); it != components.end()) {
            components.erase(it);
        }
    }

    std::string getTag() const {
        return tag;
    }

    unsigned long getId() const {
        return id;
    }


    void destroy() {
        alive = false;
    }

    bool isAlive() const {
        return alive;
    }
};