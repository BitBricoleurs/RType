//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <vector>
#include "Registry.hpp"
#include "EventHandler.hpp"


namespace GameEngine {
    class GameEngine
    {
        public:
            GameEngine();
            ~GameEngine();

            void update() {
                registry->getEventHandler()->update();
            }
        private:
            std::unique_ptr<Registry> registry;
    };
} // namespace GameEngine