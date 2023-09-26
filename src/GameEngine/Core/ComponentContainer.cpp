//
// Created by Theophilus Homawoo on 25/09/2023.
//

#include "ComponentContainer.hpp"

namespace GameEngine {
    std::vector<std::optional<std::shared_ptr<IComponent>>> ComponentsContainer::getComponents(size_t componentType) {
        return componentsContainer[componentType];
    }
    std::optional<std::shared_ptr<IComponent>> ComponentsContainer::getComponent(size_t entityID, size_t componentType) {
        return componentsContainer[componentType][entityID];
    }
    std::vector<size_t> ComponentsContainer::getEntitiesWithComponent(size_t componentType) {
        std::vector<size_t> entities;
        for (size_t i = 0; i < componentsContainer[componentType].size(); i++) {
            if (componentsContainer[componentType][i].has_value()) {
                entities.push_back(i);
            }
        }
        return entities;
    }
    std::vector<std::optional<std::shared_ptr<IComponent>>> ComponentsContainer::getComponentsFromEntity(size_t entityID) {
        std::vector<std::optional<std::shared_ptr<IComponent>>> components;
        for (auto componentType : componentsContainer) {
            components.push_back(componentType.second[entityID]);
        }
        return components;
    }

    void ComponentsContainer::bindComponentToEntity(size_t entityID, size_t componentType, std::optional<std::shared_ptr<IComponent>> component) {
        if(entityID >= componentsContainer[componentType].size()) {
            componentsContainer[componentType].resize(entityID + 1);
        }
        componentsContainer[componentType][entityID] = component;
    }
    void ComponentsContainer::unbindComponentFromEntity(size_t entityID, size_t componentType) {
        if(entityID < componentsContainer[componentType].size()) {
            componentsContainer[componentType][entityID] = std::nullopt;

            while (!componentsContainer[componentType].empty() &&
                   !componentsContainer[componentType].back().has_value()) {
                componentsContainer[componentType].pop_back();
            }
        }
    }

    void ComponentsContainer::deleteEntity(size_t entityID) {
        freeMemorySlots.push_back(entityID);

        for (auto& [componentType, components] : componentsContainer) {
            if (entityID < components.size()) {
                components[entityID] = std::nullopt;
            }
        }
    }
    size_t ComponentsContainer::createEntity() {
        size_t entityID;
        if (!freeMemorySlots.empty()) {
            entityID = freeMemorySlots.back();
            freeMemorySlots.pop_back();
        } else {
            if (!componentsContainer.empty()) {
                entityID = componentsContainer.begin()->second.size();
            } else {
                entityID = 0;
            }
        }
        return entityID;

    }
    size_t ComponentsContainer::createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components) {
        size_t entityID = createEntity();
        for (size_t i = 0; i < components.size(); i++) {
            bindComponentToEntity(entityID, i, components[i]);
        }
        return entityID;
    }

    void ComponentsContainer::clear() {
        for (auto& componentTypePair : componentsContainer) {
            componentTypePair.second.clear();
        }
        freeMemorySlots.clear();
    }

}
