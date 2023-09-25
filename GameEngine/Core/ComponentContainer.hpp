//
// Created by Theophilus Homawoo on 25/09/2023.
//

#pragma once

#include <iostream>
#include <unordered_map>
#include <optional>
#include <vector>
#include <memory>

#include "IComponent.hpp"

namespace GameEngine {
    class ComponentsContainer {
    public:
        std::vector<std::optional<std::shared_ptr<IComponent>>> getComponents(size_t componentType);
        std::optional<std::shared_ptr<IComponent>> getComponent(size_t entityID, size_t componentType);
        std::vector<size_t> getEntitiesWithComponent(size_t componentType);
        std::vector<std::optional<std::shared_ptr<IComponent>>> getComponentsFromEntity(size_t entityID);

        void bindComponentToEntity(size_t entityID, size_t componentType, std::optional<std::shared_ptr<IComponent>> component);
        void unbindComponentFromEntity(size_t entityID, size_t componentType);

        void deleteEntity(size_t entityID);
        size_t createEntity();
        size_t createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components);

        void clear();

    private:
        std::unordered_map<size_t, std::vector<std::optional<std::shared_ptr<IComponent>>>> componentsContainer;
        std::vector<size_t> freeMemorySlots;
    };
}