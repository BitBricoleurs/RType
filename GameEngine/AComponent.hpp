//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include "IComponent.hpp"


namespace GameEngine {
    class AComponent : public IComponent {
        public:
            AComponent();
            ~AComponent();

            size_t getComponentType() override { return componentType;}
            void incrementBindedEntities() override { bindedEntities++; }
            void decrementBindedEntities() override { bindedEntities--; }
            int getBindedEntities() override { return bindedEntities; }
        private:
            size_t componentType;
            int bindedEntities;
    };
} // namespace GameEngine