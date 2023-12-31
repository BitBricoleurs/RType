//
// Created by Theophilus Homawoo on 25/09/2023.
//

#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <optional>
#include <vector>
#include <memory>
#include <mutex>
#include "IComponent.hpp"

namespace GameEngine {
    class ComponentsContainer {
    public:
        ComponentsContainer() : componentsContainer(), freeMemorySlots(), maxEntityID(1) {};
        ~ComponentsContainer() = default;

        std::vector<std::optional<std::shared_ptr<IComponent>>> getComponents(size_t componentType);
        std::optional<std::shared_ptr<IComponent>> getComponent(size_t entityID, size_t componentType);
        std::vector<size_t> getEntitiesWithComponent(size_t componentType);
        size_t getEntityWithUniqueComponent(size_t componentType);
        std::vector<size_t> getEntitiesWithComponent(size_t componentType, size_t secondComponentType);
        std::vector<std::optional<std::shared_ptr<IComponent>>> getComponentsFromEntity(size_t entityID);

        void bindComponentToEntity(size_t entityID, std::optional<std::shared_ptr<IComponent>> component);
        void unbindComponentFromEntity(size_t entityID, size_t componentType);

        void deleteEntity(size_t entityID);
        size_t createEntity(bool persistent = false);
        size_t createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components, bool persistent = false);

        void clear();

        std::mutex getContainerMutex() const;

    private:
        std::unordered_map<size_t, std::vector<std::optional<std::shared_ptr<IComponent>>>> componentsContainer;
        std::vector<size_t> freeMemorySlots;
        size_t maxEntityID = 1;
        mutable std::mutex containerMutex;
        std::unordered_set<size_t> persistentEntities;
    };
}