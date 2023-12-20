#pragma once

#include "Entity.h"

class EntityManager {
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Entity>> toAdd;
    std::map<std::string, std::vector<std::shared_ptr<Entity>>> entityMap;

    unsigned long totalEntities = 0;
public:
    EntityManager() = default;

    std::shared_ptr<Entity> addEntity(const std::string &tag) {
        auto e = std::shared_ptr<Entity>(new Entity(++totalEntities, tag));
        toAdd.push_back(e);

        return e;
    }

    void update() {
        for (const auto &e: toAdd) {
            entities.push_back(e);
            entityMap[e->getTag()].push_back(e);
        }
        toAdd.clear();

        entities.erase(std::remove_if(entities.begin(), entities.end(),
                                      [](const std::shared_ptr<Entity> &e) {
                                          return !e->isAlive();
                                      }), entities.end());

        for (auto &pair: entityMap) {
            pair.second.erase(remove_if(pair.second.begin(), pair.second.end(),
                                        [](const std::shared_ptr<Entity>& e) {
                                            return !e->isAlive();
                                        }), pair.second.end());
        }
    }

    std::vector<std::shared_ptr<Entity>> getEntities() {
        return entities;
    }

    std::vector<std::shared_ptr<Entity>> getEntities(const std::string &tag) {
        return entityMap[tag];
    }
};
