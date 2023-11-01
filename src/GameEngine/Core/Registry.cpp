#include "Registry.hpp"

namespace GameEngine {
    Registry::Registry() = default;
    Registry::~Registry() = default;

    void Registry::clear() {
        componentsContainer.clear();
        for (auto it = systemMap.begin(); it != systemMap.end(); ) {
            if (persistentSystems.find(it->first) == persistentSystems.end()) {
                it = systemMap.erase(it);
            } else {
                ++it;
            }
        }
        systemOrder.clear();
        systemsNeedSorting = true;
    }

    const ComponentsContainer& Registry::getComponentsContainer() const {
        return componentsContainer;
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
    size_t Registry::createEntity(bool persistent) {
        return componentsContainer.createEntity(persistent);
    }
    size_t Registry::createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components, bool persistent) {
        return componentsContainer.createEntity(components, persistent);
    }

    void Registry::addSystem(const std::string& systemName, std::shared_ptr<ISystem> system, int priority, bool persistent) {
        systemMap[systemName] = {system, priority};
        systemsNeedSorting = true;
        if (persistent) {
            persistentSystems.insert(systemName);
        }
    }

    void Registry::setPersistent(const std::string& systemName, bool persistent) {
        if (persistent) {
            persistentSystems.insert(systemName);
        } else {
            persistentSystems.erase(systemName);
        }
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

            systemOrder.clear();
            for (const auto& item : sortedSystems) {
                systemOrder.push_back(item.first);
            }

            systemsNeedSorting = false;
        }

        for (auto &name : systemOrder) {
            std::pair<std::shared_ptr<ISystem>, int> systemPair = systemMap[name];
            systemPair.first->update(componentsContainer, eventHandler);
        }
        eventHandler.processEventQueue(componentsContainer);
    }
}
