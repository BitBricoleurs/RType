//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <vector>
#include <unordered_map>
#include <optional>
#include <any>
#include <memory>
#include "IComponent.hpp"

namespace GameEngine {
    class EventHandler;

    class ISystem
    {
        public:
            virtual void update(std::unordered_map<size_t, std::vector<std::optional<std::shared_ptr<IComponent>>>> componentsContainer, const EventHandler& eventHandler) = 0;
        private:
    };
} // namespace GameEngine
