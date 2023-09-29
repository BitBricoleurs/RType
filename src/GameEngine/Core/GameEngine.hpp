//
// Created by Theophilus Homawoo on 24/09/2023.
//

#pragma once

#include <utility>
#include <thread>
#include <vector>
#include <tuple>
#include <functional>

#include "Registry.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "IComponent.hpp"
#include "Timer.hpp"

namespace GameEngine {

    class GameEngine {
    public:
        GameEngine();
        ~GameEngine();

        size_t createEntity();
        size_t createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components);

        void bindComponentToEntity(size_t entityID, std::optional<std::shared_ptr<IComponent>> component);
        void unbindComponentFromEntity(size_t entityID, size_t componentType);
        void addSystem(const std::string& systemName, std::shared_ptr<ISystem> system, int priority = 1);

        void bindSceneInitiation(const std::string& sceneName, std::function<void(Registry&)> sceneInitiation);
        void changeScene(const std::string& sceneName);

        void setTickSpeed(double newTickSpeed);
        void scheduleEvent(const std::string& eventName, size_t interval);
        void unscheduleEvent(const std::string& eventName);

        void setContinuousEvent(const std::string& eventName, const std::string& continuousEventName);
        void removeContinuousEvent(const std::string& eventName);

        void run();

        void addEvent(const std::string& eventName, std::shared_ptr<ISystem> system);
        void addEvent(const std::string& eventName, std::function<void()> function);
        void addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems);

        void deleteEvent(const std::string& eventName);

    private:
        void update();
        void stop();

        Registry registry;
        EventHandler eventHandler;
        double tickSpeed;
        std::vector<std::tuple<std::string, size_t, size_t>> scheduledEvents;
        bool isRunning;
    };
} // namespace GameEngine