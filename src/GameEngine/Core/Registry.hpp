//
// Created by Theophilus Homawoo on 24/09/2023.
//

#pragma once

#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <optional>
#include <map>
#include <functional>
#include <memory>
#include <future>
#include <mutex>
#include <thread>

#include "ComponentContainer.hpp"
#include "IComponent.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "DynamicLibraryHandler.hpp"

namespace GameEngine {

    class Registry {
    public:
        Registry(bool isMultiThreaded = false);
        ~Registry();

        const ComponentsContainer& getComponentsContainer() const;

        std::vector<std::optional<std::shared_ptr<IComponent>>> getComponents(size_t componentType);
        std::optional<std::shared_ptr<IComponent>> getComponent(size_t entityID, size_t componentType);
        std::vector<size_t> getEntitiesWithComponent(size_t componentType);
        std::vector<std::optional<std::shared_ptr<IComponent>>> getComponentsFromEntity(size_t entityID);

        void bindComponentToEntity(size_t entityID, std::optional<std::shared_ptr<IComponent>> component);
        void unbindComponentFromEntity(size_t entityID, size_t componentType);

        void deleteEntity(size_t entityID);
        size_t createEntity();
        size_t createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components);

        void addSystem(const std::string& systemName, std::shared_ptr<ISystem> system);
        void addSystem(const std::string& systemName, std::shared_ptr<ISystem> system, int priority);
        void addSystem(const std::string& systemName, const std::string& libraryPath, int priority);
        void deleteSystem(const std::string& systemName);

        void updateSystems(EventHandler& eventHandler);

        void clear();

    private:
        ComponentsContainer componentsContainer;
        std::unordered_map<std::string, std::pair<std::shared_ptr<ISystem>, int>> systemMap;
        std::unordered_map<std::string, std::unique_ptr<DynamicLibraryHandler>> libraryHandlers;
        std::vector<std::string> systemOrder;
        bool systemsNeedSorting = true;
        bool isMultiThreaded;
    };
}
