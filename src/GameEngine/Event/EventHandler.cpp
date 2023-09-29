//
// Created by Theophilus Homawoo on 24/09/2023.
//

#include "EventHandler.hpp"

namespace GameEngine {

    EventHandler::EventHandler() = default;
    EventHandler::~EventHandler() = default;

    void EventHandler::addEvent(const std::string& eventName, std::shared_ptr<GameEngine::ISystem> system) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventMap[eventName].push_back(system);
    }

    void EventHandler::addEvent(const std::string& eventName, std::function<void()> function) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventFunctionMap[eventName] = function;
    }

    void EventHandler::addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventMap[eventName].insert(eventMap[eventName].end(), systems.begin(), systems.end());
    }

    void EventHandler::queueEvent(const std::string& eventName) {

        std::cout << eventName << std::endl;
        eventQueue.push(eventName);
    }

    void EventHandler::processEventQueue(ComponentsContainer& componentsContainer) {
        while (!eventQueue.empty()) {
            auto eventName = eventQueue.front();
            triggerEvent(eventName, componentsContainer);
            eventQueue.pop();
        }
    }

    void EventHandler::triggerEvent(const std::string& eventName, ComponentsContainer& componentsContainer) {
        if (eventMap.find(eventName) != eventMap.end()) {
            for (auto& system : eventMap[eventName]) {
                system->update(componentsContainer, *this);
            }
        }
        if (eventFunctionMap.find(eventName) != eventFunctionMap.end()) {
            eventFunctionMap[eventName]();
        }
    }

    void EventHandler::deleteEvent(const std::string& eventName) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventMap.erase(eventName);
    }

}  // namespace GameEngine
