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

#include "IComponent.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"

namespace GameEngine {

    class Registry {
    public:
        Registry();
        ~Registry();

        const std::unordered_map<size_t, std::vector<std::optional<std::shared_ptr<IComponent>>>>& getComponentsContainer() const;

        void bindSceneInitiation(const std::string& sceneName, std::function<void(Registry&)> sceneInitiation);
        void changeScene(const std::string& sceneName);

        std::vector<std::optional<std::shared_ptr<IComponent>>> getComponents(size_t componentType);
        std::optional<std::shared_ptr<IComponent>> getComponent(size_t entityID, size_t componentType);
        std::vector<size_t> getEntitiesWithComponent(size_t componentType);
        std::vector<std::optional<std::shared_ptr<IComponent>>> getComponentsFromEntity(size_t entityID);

        void bindComponentToEntity(size_t entityID, size_t componentType, std::optional<std::shared_ptr<IComponent>> component);
        void unbindComponentFromEntity(size_t entityID, size_t componentType);

        void deleteEntity(size_t entityID);
        size_t createEntity();
        size_t createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components);

        void addSystem(const std::string& systemName, std::shared_ptr<ISystem> system);
        void addSystem(const std::string& systemName, std::shared_ptr<ISystem> system, int priority);
        void deleteSystem(const std::string& systemName);

        void updateSystems(EventHandler& eventHandler);

    private:
        std::vector<size_t> freeMemorySlots;
        std::unordered_map<size_t, std::vector<std::optional<std::shared_ptr<IComponent>>>> componentsContainer;
        std::map<std::string, std::pair<std::shared_ptr<ISystem>, int>> systemMap;
        std::unordered_map<std::string, std::function<void(Registry&)>> sceneMap;
        bool systemsNeedSorting = true;
    };
}
