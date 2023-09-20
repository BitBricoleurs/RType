//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <vector>
#include "Registry.hpp"
#include "EventHandler.hpp"
#include "Timer.hpp"

namespace GameEngine {
    class GameEngine
    {
        public:
            GameEngine() : registry(std::make_unique<Registry>()), useEngineLoop(true), tickRate(30) {}
            ~GameEngine() = default;

            void setTickRate(size_t tickRate) { this->tickRate = tickRate; }
            void setUseEngineLoop(bool useEngineLoop) { this->useEngineLoop = useEngineLoop; }

            void run() {
                Timer timer;
                while (useEngineLoop) {
                    timer.start();
                    update();
                    timer.stop();
                    if (timer.getElapsedTime() < 1000 / tickRate) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / tickRate - timer.getElapsedTime()));
                    }
                }
            }

            void triggerRegularEvent(std::string eventName, size_t ticks) {
                if (regularEventMap.find(eventName) == regularEventMap.end()) {
                    regularEventMap[eventName] = ticks;
                }
                if (regularEventMap[eventName] == 0) {
                    regularEventMap[eventName] = ticks;
                    registry->getEventHandler()->triggerEvent(eventName);
                }
                regularEventMap[eventName]--;
            }

            void update() {
                registry->updateSystems();
                registry->getEventHandler()->update();
            }
        private:
            std::shared_ptr<Registry> registry;
            bool useEngineLoop;
            size_t tickRate;
            std::unordered_map<std::string, size_t> regularEventMap;
    };
} // namespace GameEngine