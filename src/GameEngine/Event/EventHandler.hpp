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
#include "ComponentContainer.hpp"

namespace GameEngine {

    class EventHandler {
    public:
        EventHandler();
        ~EventHandler();

        void addEvent(const std::string& eventName, std::shared_ptr<GameEngine::ISystem> system);
        void addEvent(const std::string& eventName, std::function<void()> function);
        void addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems);
        void queueEvent(const std::string& eventName);
        void processEventQueue(const ComponentsContainer& componentsContainer);
        void triggerEvent(const std::string& eventName, const ComponentsContainer& componentsContainer);
        void deleteEvent(const std::string& eventName);
        std::string getTriggeredEvent() const { return eventQueue.front(); }

    private:
        std::unordered_map<std::string, std::vector<std::shared_ptr<ISystem>>> eventMap;
        std::unordered_map<std::string, std::function<void()>> eventFunctionMap;
        std::queue<std::string> eventQueue;
        std::mutex eventMutex;
    };

}  // namespace GameEngine
