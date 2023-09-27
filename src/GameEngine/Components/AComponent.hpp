//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include "IComponent.hpp"

namespace GameEngine {
    class AComponent : public IComponent {
        public:
            AComponent() = default;
            ~AComponent() override = default;

            size_t getComponentType() override { return componentType;}
            void setComponentType(size_t newComponentType) { componentType = newComponentType; }
        private:
            size_t componentType;
    };
} // namespace GameEngine
