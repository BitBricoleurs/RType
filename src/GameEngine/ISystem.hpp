//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <vector>
#include <unordered_map>
#include <optional>
#include <any>
#include "EventHandler.hpp"

namespace GameEngine {
    class ISystem
    {
        public:
            virtual void update(std::unordered_map<size_t, std::vector<std::optional<std::any>>> componentsContainer, std::shared_ptr<EventHandler> eventHandler) = 0;
        private:
    };
} // namespace GameEngine
