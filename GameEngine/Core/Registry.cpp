#include "Registry.hpp"

namespace GameEngine {
    Registry::Registry() = default;
    Registry::~Registry() = default;

    const std::unordered_map<size_t, std::vector<std::optional<std::shared_ptr<IComponent>>>>& Registry::getComponentsContainer() const {
        return componentsContainer;
    }

    void Registry::bindSceneInitiation(const std::string& sceneName, std::function<void(Registry&)> sceneInitiation) {
        sceneMap[sceneName] = sceneInitiation;
    }

    void Registry::changeScene(const std::string &sceneName) {
        for (auto& componentTypePair : componentsContainer) {
            componentTypePair.second.clear();
        }
        freeMemorySlots.clear();

        auto it = sceneMap.find(sceneName);
        if (it != sceneMap.end()) {
            it->second(*this);
        } else {
            std::cerr << "Error: Scene '" << sceneName << "' not found!" << std::endl; // NE PAS OUBLIER LES CUSTOMS ERROS
        }
    }

    std::vector<std::optional<std::shared_ptr<IComponent>>> Registry::getComponents(size_t componentType) {
        return componentsContainer[componentType];
    }
    std::optional<std::shared_ptr<IComponent>> Registry::getComponent(size_t entityID, size_t componentType) {
        return componentsContainer[componentType][entityID];
    }
    std::vector<size_t> Registry::getEntitiesWithComponent(size_t componentType) {
        std::vector<size_t> entities;
        for (size_t i = 0; i < componentsContainer[componentType].size(); i++) {
            if (componentsContainer[componentType][i].has_value()) {
                entities.push_back(i);
            }
        }
        return entities;
    }
    std::vector<std::optional<std::shared_ptr<IComponent>>> Registry::getComponentsFromEntity(size_t entityID) {
        std::vector<std::optional<std::shared_ptr<IComponent>>> components;
        for (auto componentType : componentsContainer) {
            components.push_back(componentType.second[entityID]);
        }
        return components;
    }

    void Registry::bindComponentToEntity(size_t entityID, size_t componentType, std::optional<std::shared_ptr<IComponent>> component) {
        if(entityID >= componentsContainer[componentType].size()) {
            componentsContainer[componentType].resize(entityID + 1);
        }
        componentsContainer[componentType][entityID] = component;
    }
    void Registry::unbindComponentFromEntity(size_t entityID, size_t componentType) {
        if(entityID < componentsContainer[componentType].size()) {
            componentsContainer[componentType][entityID] = std::nullopt;

            while (!componentsContainer[componentType].empty() &&
                   !componentsContainer[componentType].back().has_value()) {
                componentsContainer[componentType].pop_back();
            }
        }
    }

    void Registry::deleteEntity(size_t entityID) {
        freeMemorySlots.push_back(entityID);

        for (auto& [componentType, components] : componentsContainer) {
            if (entityID < components.size()) {
                components[entityID] = std::nullopt;
            }
        }
    }
    size_t Registry::createEntity() {
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
    size_t Registry::createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components) {
        size_t entityID = createEntity();
        for (size_t i = 0; i < components.size(); i++) {
            bindComponentToEntity(entityID, i, components[i]);
        }
        return entityID;
    }

    void Registry::addSystem(const std::string& systemName, std::shared_ptr<ISystem> system) {
        systemMap[systemName] = {system, 1};
        systemsNeedSorting = true;
    }
    void Registry::addSystem(const std::string& systemName, std::shared_ptr<ISystem> system, int priority) {
        systemMap[systemName] = {system, priority};
        systemsNeedSorting = true;
    }
    void Registry::deleteSystem(const std::string& systemName) {
        systemMap.erase(systemName);
    }

    void Registry::updateSystems(EventHandler& eventHandler) {
        if (systemsNeedSorting) {
            std::vector<std::pair<std::string, std::pair<std::shared_ptr<ISystem>, int>>> sortedSystems(systemMap.begin(), systemMap.end());
            std::sort(sortedSystems.begin(), sortedSystems.end(), [](const auto& a, const auto& b) {
                return a.second.second < b.second.second;
            });

            systemMap.clear();
            for (const auto& item : sortedSystems) {
                systemMap[item.first] = item.second;
            }

            systemsNeedSorting = false;
        }

        for (auto& [name, systemPair] : systemMap) {
            systemPair.first->update(componentsContainer, eventHandler);
        }
        eventHandler.processEventQueue(componentsContainer);
    }
}
