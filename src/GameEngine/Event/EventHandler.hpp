//
// Created by Theophilus Homawoo on 24/09/2023.
//

#pragma once

#include <functional>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <queue>
#include <mutex>
#include <any>
#include <utility>
#include "IComponent.hpp"
#include "ISystem.hpp"
#include "ComponentContainer.hpp"
#include <set>

namespace GameEngine {

    class EventHandler {
    public:
        EventHandler();
        ~EventHandler();

        void addEvent(const std::string& eventName, std::shared_ptr<GameEngine::ISystem> system);
        void addEvent(const std::string& eventName, std::function<void()> function);
        void addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems);
        void queueEvent(const std::string& eventName, const std::any& eventData = {});
        void processEventQueue(ComponentsContainer& componentsContainer);
        void triggerEvent(const std::string& eventName, ComponentsContainer& componentsContainer);
        void deleteEvent(const std::string& eventName);
        void scheduleEvent(const std::string& eventName, size_t interval, const std::any& eventData = {});
        void unscheduleEvent(const std::string& eventName);
        void updateScheduledEvents();
        std::pair<std::string, std::any> getTriggeredEvent() const { return eventQueue.front(); }
        void setContinuousEvent(const std::string& eventName, const std::string& continuousEventName, const std::any& eventData = {});
        void removeContinuousEvent(const std::string& eventName);

    private:
        std::unordered_map<std::string, std::vector<std::shared_ptr<ISystem>>> eventMap;
        std::unordered_map<std::string, std::function<void()>> eventFunctionMap;
        std::map<std::string, std::pair<std::string, std::any>> continuousEvents;
        std::set<std::string> activeContinuousEvents;
        std::queue<std::pair<std::string, std::any>> eventQueue;
        std::vector<std::tuple<std::string, size_t, size_t, std::any>> scheduledEvents;
        std::mutex eventMutex;
    };

}  // namespace GameEngine