//
// Created by Theophilus Homawoo on 24/09/2023.
//

#include "EventHandler.hpp"

namespace GameEngine {

    bool compareAny(const std::any& a, const std::any& b) {
        if (a.type() != b.type()) return false;

        size_t typeHash = a.type().hash_code();

        static const std::unordered_map<size_t, std::function<bool(const std::any&, const std::any&)>> comparators = {
            { typeid(int).hash_code(), [](const std::any& a, const std::any& b) { return std::any_cast<int>(a) == std::any_cast<int>(b); } },
            { typeid(size_t).hash_code(), [](const std::any& a, const std::any& b) { return std::any_cast<size_t>(a) == std::any_cast<size_t>(b); } },
            { typeid(float).hash_code(), [](const std::any& a, const std::any& b) { return std::any_cast<float>(a) == std::any_cast<float>(b); } },
            { typeid(double).hash_code(), [](const std::any& a, const std::any& b) { return std::any_cast<double>(a) == std::any_cast<double>(b); } },
            { typeid(std::string).hash_code(), [](const std::any& a, const std::any& b) { return std::any_cast<std::string>(a) == std::any_cast<std::string>(b); } },
            { typeid(bool).hash_code(), [](const std::any& a, const std::any& b) { return std::any_cast<bool>(a) == std::any_cast<bool>(b); } },
            {typeid(std::pair<size_t, size_t>).hash_code(), [](const std::any& a, const std::any& b) {
                auto [a1, a2] = std::any_cast<std::pair<size_t, size_t>>(a);
                auto [b1, b2] = std::any_cast<std::pair<size_t, size_t>>(b);
                return a1 == b1 && a2 == b2;
            } },
            {typeid(std::pair<size_t, std::string>).hash_code(), [](const std::any& a, const std::any& b) {
                auto [a1, a2] = std::any_cast<std::pair<size_t, std::string>>(a);
                auto [b1, b2] = std::any_cast<std::pair<size_t, std::string>>(b);
                return a1 == b1 && a2 == b2;
            } },
            {typeid(std::pair<std::string, std::string>).hash_code(), [](const std::any& a, const std::any& b) {
                auto [a1, a2] = std::any_cast<std::pair<std::string, std::string>>(a);
                auto [b1, b2] = std::any_cast<std::pair<std::string, std::string>>(b);
                return a1 == b1 && a2 == b2;
            } },
        };

        auto it = comparators.find(typeHash);
        if (it != comparators.end()) {
            return it->second(a, b);
        }
    return false;
}

    EventHandler::EventHandler() = default;
    EventHandler::~EventHandler() = default;

    void EventHandler::clear() {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventMap.clear();
        eventFunctionMap.clear();
        eventFunctionMapWithAny.clear();
        continuousEvents.clear();
        activeContinuousEvents.clear();
        eventQueue = std::queue<std::pair<std::string, std::any>>();
        scheduledEvents.clear();
    }

    void EventHandler::addEvent(const std::string& eventName, std::shared_ptr<GameEngine::ISystem> system) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventMap[eventName].push_back(system);
    }

    void EventHandler::addEvent(const std::string& eventName, std::function<void()> function) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventFunctionMap[eventName] = function;
    }


    void EventHandler::addEvent(const std::string& eventName, std::function<void(const std::any&)> function) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventFunctionMapWithAny[eventName] = function;
    }

    void EventHandler::addEvent(const std::string& eventName, const std::vector<std::shared_ptr<ISystem>>& systems) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventMap[eventName].insert(eventMap[eventName].end(), systems.begin(), systems.end());
    }

    void EventHandler::queueEvent(const std::string& eventName, const std::any& eventData) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventQueue.push({eventName, eventData});

        if (continuousEvents.find(eventName) != continuousEvents.end()) {
            activeContinuousEvents.insert(eventName);
        }
        for (const auto& pair : continuousEvents) {
            if (pair.second.first == eventName) {
                activeContinuousEvents.erase(pair.first);
            }
        }
    }

    void EventHandler::processEventQueue(ComponentsContainer& componentsContainer) {
        while (!eventQueue.empty()) {
            auto[eventName, eventData] = eventQueue.front();
            triggerEvent(eventName, componentsContainer);
            if (eventName == eventQueue.front().first) {
                eventQueue.pop();
            } else {
                break;
            }
        }

        for (const auto& eventName : activeContinuousEvents) {
            eventQueue.push({eventName, continuousEvents[eventName].second});
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
        if (eventFunctionMapWithAny.find(eventName) != eventFunctionMapWithAny.end()) {
            auto it = eventQueue.front();
            if (it.second.type() == typeid(void)) {
                std::any empty;
                eventFunctionMapWithAny[eventName](empty);
            } else {
                eventFunctionMapWithAny[eventName](eventQueue.front().second);
            }
        }
    }

    void EventHandler::deleteEvent(const std::string& eventName) {
        std::lock_guard<std::mutex> lock(eventMutex);
        eventMap.erase(eventName);
    }

    void EventHandler::scheduleEvent(const std::string& eventName, size_t interval, const std::any& eventData, size_t repeat) {
        scheduledEvents.emplace_back(eventName, interval, 0, eventData, repeat, 0);
    }

    void EventHandler::unscheduleEvent(const std::string& eventName, const std::any& eventData) {
        scheduledEvents.erase(std::remove_if(scheduledEvents.begin(), scheduledEvents.end(),
            [&eventName, &eventData](auto& event) {
                auto& [name, interval, counter, data, maxRepeats, currentRepeats] = event;
                if (eventData.type() == typeid(void)) {
                    return name == eventName;
                }
                return name == eventName && GameEngine::compareAny(data, eventData);
            }),
        scheduledEvents.end());
    }

    void EventHandler::updateScheduledEvents() {
        for (auto& event : scheduledEvents) {
            auto& [eventName, interval, counter, data, maxRepeat, currentRepeats] = event;
            counter++;
            if ((maxRepeat == 0 || currentRepeats < maxRepeat) && counter >= interval) {
                queueEvent(eventName, data);
                counter = 0;
                currentRepeats++;
            }
        }

        scheduledEvents.erase(std::remove_if(scheduledEvents.begin(), scheduledEvents.end(), [](auto& event) {
            auto& [name, interval, counter, data, maxRepeats, currentRepeats] = event;
            return maxRepeats != 0 && currentRepeats >= maxRepeats;
        }), scheduledEvents.end());
    }

    void EventHandler::setContinuousEvent(const std::string& continuousEvent, const std::string& stopEvent, const std::any& eventData) {
        continuousEvents[continuousEvent] = {stopEvent, eventData};
    }

    void EventHandler::removeContinuousEvent(const std::string& eventName) {
        continuousEvents.erase(eventName);
    }

}  // namespace GameEngine