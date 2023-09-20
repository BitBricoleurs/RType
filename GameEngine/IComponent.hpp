//
// Created by Theophilus Homawoo on 19/09/2023.
//

#pragma once

#include <iostream>

namespace GameEngine {
    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual size_t getComponentType() = 0;
            virtual void incrementBindedEntities() = 0;
            virtual void decrementBindedEntities() = 0;
            virtual int getBindedEntities() = 0;
    };
} // namespace GameEngine
