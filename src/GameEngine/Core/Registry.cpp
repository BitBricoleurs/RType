#include "Registry.hpp"
#include "GameEngine.hpp"

#ifdef _WIN32
#include "WindowsDynamicLibraryHandler.hpp"
#else
#include "UnixDynamicLibraryHandler.hpp"
#endif


namespace GameEngine {

    using CreateSystemFunc = std::shared_ptr<ISystem>(*)();

    Registry::Registry(bool isMultiThreaded) : componentsContainer(), systemMap(), systemOrder(), systemsNeedSorting(true), isMultiThreaded(isMultiThreaded) {
        GameEngine::registerCommand("clearRegistry", [this](const std::vector<std::string>& args) -> std::string {
            if (args.size() >= 1) {
                if (args[0] == "true") {
                    this->clear();
                    return "Registry cleared.\n";
                } else {
                    return "Argument must be true.\n";
                }
            } else {
                return "Not enough arguments provided for clearRegistry command.\n";
            }
        });

        GameEngine::registerCommand("changeSystemPriority", [this](const std::vector<std::string>& args) -> std::string {
            if (args.size() >= 2) {
                std::string systemName = args[0];
                int priority = std::stoi(args[1]);
                if (systemMap.find(systemName) != systemMap.end()) {
                    systemMap[systemName].second = priority;
                    systemsNeedSorting = true;
                    return "System priority changed.\n";
                } else {
                    return "System not found.\n";
                }
            } else {
                return "Not enough arguments provided for changeSystemPriority command.\n";
            }
        });
    }

    Registry::~Registry() = default;

    void Registry::clear() {
        componentsContainer.clear();
        systemMap.clear();
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
    void Registry::addSystem(const std::string &systemName, const std::string &libraryPath, int priority) {
        std::unique_ptr<DynamicLibraryHandler> libraryHandler;
        #ifdef _WIN32
        libraryHandler = std::make_unique<WindowsDynamicLibraryHandler>();
        #else
        libraryHandler = std::make_unique<UnixDynamicLibraryHandler>();
        #endif

        if (!libraryHandler->loadLibrary(libraryPath)) {
            return;
        }

        auto createSystem = libraryHandler->getFunction("createSystem");
        if (!createSystem) {
            return;
        }
        auto systemCreator = reinterpret_cast<CreateSystemFunc>(createSystem.target<void*>());
        if (!systemCreator) {
            return;
        }

        std::shared_ptr<ISystem> systemInstance = systemCreator();
        if (!systemInstance) {
            return;
        }

        addSystem(systemName, systemInstance, priority);
        libraryHandlers[systemName] = std::move(libraryHandler);
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

        if(isMultiThreaded) {
            std::vector<std::thread> threads;
            for (auto &name : systemOrder) {
                std::pair<std::shared_ptr<ISystem>, int> systemPair = systemMap[name];
                threads.push_back(std::thread([systemPair, &eventHandler, this]() {
                    systemPair.first->update(componentsContainer, eventHandler);
                }));
            }

            for (auto &thread : threads) {
                if(thread.joinable()) {
                    thread.join();
                }
            }
        } else {
            for (auto &name : systemOrder) {
                std::pair<std::shared_ptr<ISystem>, int> systemPair = systemMap[name];
                systemPair.first->update(componentsContainer, eventHandler);
            }
        }
        eventHandler.processEventQueue(componentsContainer);
    }
}
