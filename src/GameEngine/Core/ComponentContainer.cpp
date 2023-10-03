//
// Created by Theophilus Homawoo on 25/09/2023.
//

#include "ComponentContainer.hpp"
#include "AComponent.hpp"

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
            if (componentType.second.size() > entityID && componentType.second[entityID].has_value()) {
                components.push_back(componentType.second[entityID]);
            }
        }
        return components;
    }

    void ComponentsContainer::bindComponentToEntity(size_t entityID, std::optional<std::shared_ptr<IComponent>> component) {
        if (!component) {
            return;
        }
        size_t componentType = component.value()->getComponentType();

        std::vector<std::optional<std::shared_ptr<IComponent>>>& entityComponents = componentsContainer[componentType];

        if(entityID >= entityComponents.size()) {
            entityComponents.resize(entityID + 1, std::nullopt);
        }
        entityComponents[entityID] = component;
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
            entityID = maxEntityID++;
        }
        return entityID;
    }

    size_t ComponentsContainer::createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components) {
        size_t entityID = createEntity();
        for (size_t i = 0; i < components.size(); i++) {
            bindComponentToEntity(entityID, components[i]);
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
