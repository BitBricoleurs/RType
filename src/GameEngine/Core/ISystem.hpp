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
#include "ComponentContainer.hpp"

namespace GameEngine {
    class EventHandler;

    class ISystem
    {
        public:
            virtual void update(const ComponentsContainer& componentsContainer, const EventHandler& eventHandler) = 0;
        private:
    };
} // namespace GameEngine
