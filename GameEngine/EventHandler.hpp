//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "ISystem.hpp"


namespace GameEngine {
    class EventHandler {
        public:
            EventHandler() = default;
            ~EventHandler() = default;

            void addEvent(std::string eventName, std::shared_ptr<ISystem> system) {
                eventMap[eventName].push_back(system);
            }

            void deleteEvent(std::string eventName) {
                eventMap.erase(eventName);
            }

        private:
            std::unordered_map<std::string, std::vector<std::shared_ptr<ISystem>>> eventMap;
    };
} // namespace GameEngine
