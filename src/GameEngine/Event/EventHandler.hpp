//
// Created by Theophilus Homawoo on 24/09/2023.
//

#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <queue>
#include <mutex>
#include "IComponent.hpp"
#include "ISystem.hpp"

namespace GameEngine {

    class EventHandler {
    public:
        EventHandler();
        ~EventHandler();

        void addEvent(const std::string& eventName, std::shared_ptr<GameEngine::ISystem> system);
        void addEvent(const std::string& eventName, std::function<void()> function);
        void addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems);
        void queueEvent(const std::string& eventName);
        void processEventQueue(std::unordered_map<size_t, std::vector<std::optional<std::shared_ptr<IComponent>>>> componentsContainer);
        void triggerEvent(const std::string& eventName, std::unordered_map<size_t, std::vector<std::optional<std::shared_ptr<IComponent>>>> componentsContainer);
        void deleteEvent(const std::string& eventName);

    private:
        std::unordered_map<std::string, std::vector<std::shared_ptr<ISystem>>> eventMap;
        std::unordered_map<std::string, std::function<void()>> eventFunctionMap;
        std::queue<std::string> eventQueue;
        std::mutex eventMutex;
    };

}  // namespace GameEngine
