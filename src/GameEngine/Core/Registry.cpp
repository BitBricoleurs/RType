#include "Registry.hpp"

namespace GameEngine {
    Registry::Registry() = default;
    Registry::~Registry() = default;

    const ComponentsContainer& Registry::getComponentsContainer() const {
        return componentsContainer;
    }

    void Registry::bindSceneInitiation(const std::string& sceneName, std::function<void(Registry&)> sceneInitiation) {
        sceneMap[sceneName] = sceneInitiation;
    }

    void Registry::changeScene(const std::string &sceneName) {
        componentsContainer.clear();

        auto it = sceneMap.find(sceneName);
        if (it != sceneMap.end()) {
            it->second(*this);
        } else {
            std::cerr << "Error: Scene '" << sceneName << "' not found!" << std::endl; // NE PAS OUBLIER LES CUSTOMS ERROS
        }
    }

    std::vector<std::optional<std::shared_ptr<IComponent>>> Registry::getComponents(size_t componentType) {
        return componentsContainer.getComponents(componentType);
    }
    std::optional<std::shared_ptr<IComponent>> Registry::getComponent(size_t entityID, size_t componentType) {
        return componentsContainer.getComponent(entityID, componentType);
    }
    std::vector<size_t> Registry::getEntitiesWithComponent(size_t componentType) {
        return componentsContainer.getEntitiesWithComponent(componentType);
    }
    std::vector<std::optional<std::shared_ptr<IComponent>>> Registry::getComponentsFromEntity(size_t entityID) {
        return componentsContainer.getComponentsFromEntity(entityID);
    }

    void Registry::bindComponentToEntity(size_t entityID, std::optional<std::shared_ptr<IComponent>> component) {
        componentsContainer.bindComponentToEntity(entityID, component);
    }
    void Registry::unbindComponentFromEntity(size_t entityID, size_t componentType) {
        componentsContainer.unbindComponentFromEntity(entityID, componentType);
    }

    void Registry::deleteEntity(size_t entityID) {
        componentsContainer.deleteEntity(entityID);
    }
    size_t Registry::createEntity() {
        return componentsContainer.createEntity();
    }
    size_t Registry::createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components) {
        return componentsContainer.createEntity(components);
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
