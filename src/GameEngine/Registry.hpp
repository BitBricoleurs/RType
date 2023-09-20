//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <vector>
#include <unordered_map>
#include <map>
#include <optional>
#include <any>
#include "ISystem.hpp"


namespace GameEngine {
    class Registry {
        public:
            Registry();
            ~Registry();

            void bindSceneInitiation(std::string sceneName, std::function<void(Registry)> sceneInitiation);
            void changeScene(std::string sceneName);

            std::vector<std::optional<std::any>> getComponents(size_t componentType);
            std::optional<std::any> getComponent(size_t entityID, size_t componentType);
            std::vector<size_t> getEntitiesWithComponent(size_t componentType);
            std::vector<std::optional<std::any>> getComponentsFromEntity(size_t entityID);

            void bindComponentToEntity(size_t entityID, size_t componentType, std::optional<std::any> component);
            void unbindComponentFromEntity(size_t entityID, size_t componentType);

            void deleteEntity(size_t entityID);
            size_t createEntity();
            size_t createEntity(size_t Layer);
            size_t createEntity(std::vector<std::optional<std::any>> components);
            size_t createEntity(std::vector<std::optional<std::any>> components, size_t Layer);

            void addSystem(std::string systemName, std::shared_ptr<ISystem> system);
            void addSystem(std::string systemName, std::string systemPath);
            void addSystem(std::string systemName, std::shared_ptr<ISystem> system, std::string priority);
            void addSystem(std::string systemName, std::string systemPath, std::string priority);
            void deleteSystem(std::string systemName);

        private:
            std::vector<size_t> freeMemorySlots;
            std::unordered_map<size_t, std::vector<std::optional<std::any>>> componentsContainer;
            std::map<std::string, std::shared_ptr<ISystem>> systemMap;
            std::unordered_map<std::string, std::function<void(Registry)>> sceneMap;
    };
} // namespace GameEngine
