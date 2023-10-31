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
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

namespace GameEngine {

    class GameEngine {
        using CommandFunction = std::function<std::string(const std::vector<std::string>&)>;
    public:
        GameEngine();
        ~GameEngine();

        size_t createEntity();
        size_t createEntity(std::vector<std::optional<std::shared_ptr<IComponent>>> components);

        void bindComponentToEntity(size_t entityID, std::optional<std::shared_ptr<IComponent>> component);
        void unbindComponentFromEntity(size_t entityID, size_t componentType);
        void addSystem(const std::string& systemName, std::shared_ptr<ISystem> system, int priority = 1);

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
    private:
        void update();
        void stop();

        Registry registry;
        EventHandler eventHandler;
        std::unordered_map<std::string, std::function<void(GameEngine&)>> sceneMap;
        void launch_cpp_program(std::string path, const std::string args = "") {
            std::string basePath = LoadConfig::LoadConfig::getInstance().getExecutablePath();
            path = basePath + "/" + path;
            std::cout << "Launching: " << path << std::endl;
            #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
                std::string command = "xterm -e";
                command += "\"" + path + " " + args + "\" &";
                int ret = std::system(command.c_str());
                if (ret == -1) {
                    throw std::runtime_error("Failed to open terminal.");
                }
            #elif defined(_WIN32) || defined(_WIN64)
                std::string command = "start cmd /k ";
                command += "\"" + path + " " + args + "\"";
                int ret = std::system(command.c_str());
                if (ret == -1) {
                    throw std::runtime_error("Failed to open CMD.");
                }
            #else
                std::cout << "Unsupported OS" << std::endl;
            #endif
        }
        double tickSpeed;
        bool isRunning;
        static std::map<std::string, CommandFunction> commands;
        bool pause = false;
    };
} // namespace GameEngine