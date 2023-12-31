//
// Created by Theophilus Homawoo on 24/09/2023.
//

#pragma once

#include <utility>
#include <thread>
#include <vector>
#include <tuple>
#include <functional>
#include <sstream>
#include <thread>

#include "Registry.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"
#include "IComponent.hpp"
#include "Timer.hpp"
#include "Logger.hpp"
#include "LoadConfig.hpp"

namespace GameEngine {

    class GameEngine {
        using CommandFunction = std::function<std::string(const std::vector<std::string>&)>;
    public:
        GameEngine(bool isMultiThreaded = false);
        ~GameEngine();

        size_t createEntity(bool persistent = false);
        size_t createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components, bool persistent = false);

        void bindComponentToEntity(size_t entityID, std::optional<std::shared_ptr<IComponent>> component);
        void unbindComponentFromEntity(size_t entityID, size_t componentType);
        void addSystem(const std::string& systemName, std::shared_ptr<ISystem> system, int priority = 1, bool persistent = false);

        void bindSceneInitiation(const std::string& sceneName, std::function<void(GameEngine&)> sceneInitiation);
        void changeScene(const std::any& sceneName);

        void setTickSpeed(double newTickSpeed);
        void scheduleEvent(const std::string& eventName, size_t interval, const std::any& eventData = {}, size_t repeat = 0);
        void unscheduleEvent(const std::string& eventName, const std::any& eventData = {});

        void setContinuousEvent(const std::string& eventName, const std::string& continuousEventName);
        void removeContinuousEvent(const std::string& eventName);

        void run();

        void addEvent(const std::string& eventName, std::shared_ptr<ISystem> system);
        void queueEvent(const std::string& eventName, const std::any& eventData = {});
        void addEvent(const std::string& eventName, std::function<void()> function);
        void addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems);

        void deleteEvent(const std::string& eventName);

        static std::string handleDevConsole(std::string command);
        static void registerCommand(const std::string& command, CommandFunction function);

        EventHandler& getEventHandler();
    private:
        void update();
        void stop();

        Registry registry;
        EventHandler eventHandler;
        std::unordered_map<std::string, std::function<void(GameEngine&)>> sceneMap;

        std::thread loggerThread;

        double tickSpeed;
        bool isRunning;
        static std::map<std::string, CommandFunction> commands;
        bool pause = false;
    };
} // namespace GameEngine