//
// Created by Theophilus Homawoo on 24/09/2023.
//

#include "GameEngine.hpp"

#include <utility>

namespace GameEngine {
    GameEngine::GameEngine() : tickSpeed(1.0 / 60.0), isRunning(true) {
        eventHandler.addEvent("gameEngineStop", [this] { this->stop(); });
        eventHandler.addEvent("gameEngineChangeScene", [this](const std::any& sceneName) { this->changeScene(sceneName); });
    }

    GameEngine::~GameEngine() = default;

    size_t GameEngine::createEntity() {
        return registry.createEntity();
    }

    size_t GameEngine::createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components) {
        return registry.createEntity(std::move(components));
    }

    void GameEngine::bindComponentToEntity(size_t entityID, std::optional<std::shared_ptr<IComponent>> component) {
        registry.bindComponentToEntity(entityID, std::move(component));
    }

    void GameEngine::unbindComponentFromEntity(size_t entityID, size_t componentType) {
        registry.unbindComponentFromEntity(entityID, componentType);
    }

    void GameEngine::addSystem(const std::string& systemName, std::shared_ptr<ISystem> system, int priority) {
        registry.addSystem(systemName, std::move(system), priority);
    }

    void GameEngine::bindSceneInitiation(const std::string& sceneName, std::function<void(GameEngine&)> sceneInitiation) {
        sceneMap[sceneName] = std::move(sceneInitiation);
    }

    void GameEngine::changeScene(const std::any& sceneName) {
        try {
            auto sceneNameString = std::any_cast<std::string>(sceneName);
            if (sceneMap.find(sceneNameString) == sceneMap.end()) {
                std::cerr << "Error: Scene name not found!" << std::endl;
                return;
            }
            eventHandler.clear();
            registry.clear();
            sceneMap[sceneNameString](*this);
            eventHandler.addEvent("gameEngineStop", [this] { this->stop(); });
            eventHandler.addEvent("gameEngineChangeScene", [this](const std::any& sceneName) { this->changeScene(sceneName); });

        } catch (const std::bad_any_cast& e) {
            std::cerr << "Error: Scene name must be a string!" << std::endl;
            return;
        }
    }

    void GameEngine::setTickSpeed(double newTickSpeed) {
        tickSpeed = newTickSpeed;
    }

    void GameEngine::scheduleEvent(const std::string& eventName, size_t interval, const std::any& eventData, size_t repeat) {
        eventHandler.scheduleEvent(eventName, interval, eventData, repeat);
    }

    void GameEngine::unscheduleEvent(const std::string& eventName, const std::any& eventData) {
        eventHandler.unscheduleEvent(eventName, eventData);
    }

    void GameEngine::run() {
        Timer timer;
        double lastTickTime = 0.0;

        while (isRunning) {
            double currentTime = timer.elapsedSeconds();
            if (currentTime - lastTickTime >= tickSpeed) {
                update();
                lastTickTime = currentTime;
            } else {
                int sleepTime = static_cast<int>(tickSpeed - (currentTime - lastTickTime) * 10000 - excessiveWaitedTime);
                if (sleepTime > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
                }
            }
        }
    }

    void GameEngine::addEvent(const std::string& eventName, std::shared_ptr<ISystem> system) {
        eventHandler.addEvent(eventName, std::move(system));
    }

    void GameEngine::addEvent(const std::string& eventName, std::function<void()> function) {
        eventHandler.addEvent(eventName, std::move(function));
    }

    void GameEngine::addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems) {
        eventHandler.addEvent(eventName, systems);
    }

    void GameEngine::deleteEvent(const std::string& eventName) {
        eventHandler.deleteEvent(eventName);
    }

    void GameEngine::update() {
        registry.updateSystems(eventHandler);
        eventHandler.updateScheduledEvents();
    }

    void GameEngine::stop() {
        isRunning = false;
    }

    void GameEngine::setContinuousEvent(const std::string& eventName, const std::string& continuousEventName) {
        eventHandler.setContinuousEvent(eventName, continuousEventName);
    }

    void GameEngine::removeContinuousEvent(const std::string& eventName) {
        eventHandler.removeContinuousEvent(eventName);
    }

    void GameEngine::queueEvent(const std::string& eventName, const std::any& eventData) {
        eventHandler.queueEvent(eventName, eventData);
    }
}
