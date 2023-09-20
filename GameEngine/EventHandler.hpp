//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <unordered_map>
#include <vector>
#include "ISystem.hpp"


namespace GameEngine {
    class EventHandler {
        public:
            EventHandler();
            ~EventHandler();

            void addEvent(std::string eventName, std::shared_ptr<ISystem> system);
            void deleteEvent(std::string eventName);

        private:
            std::unordered_map<std::string, std::vector<std::shared_ptr<ISystem>>> eventMap;
    };
} // namespace GameEngine
