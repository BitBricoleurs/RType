//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "ISystem.hpp"
#include "SharedLibrary.hpp"


namespace GameEngine {
    class EventHandler {
        public:
            EventHandler() = default;
            ~EventHandler() = default;

            void addEvent(std::string eventName, std::shared_ptr<ISystem> system) {
                eventMap[eventName].push_back(system);
            }

            void addEvent(std::string eventName, std::vector<std::shared_ptr<ISystem>> systems) {
                eventMap[eventName].insert(eventMap[eventName].end(), systems.begin(), systems.end());
            }

            void addEvent(std::string eventName, std::string systemPath) {
                if (sharedLibraryMap.find(systemPath) == sharedLibraryMap.end()) {
                    sharedLibraryMap[systemPath] = std::make_shared<SharedLibrary>(systemPath);
                }
                auto system = sharedLibraryMap[systemPath]->getSystem();
                eventMap[eventName].push_back(system);
            }

            void triggerEvent(std::string eventName) {
                eventList.push_back(eventName);
            }

            void update() {
                for (auto eventName : eventList) {
                    for (auto system : eventMap[eventName]) {
                        system->update();
                    }
                }
                eventList.clear();
            }

            void deleteEvent(std::string eventName) {
                eventMap.erase(eventName);
            }

        private:
            std::unordered_map<std::string, std::vector<std::shared_ptr<ISystem>>> eventMap;
            std::vector<std::string> eventList;
            std::unordered_map<std::string, std::shared_ptr<SharedLibrary>> sharedLibraryMap;
    };
} // namespace GameEngine
