//
// Created by Clément Lagasse on 25/10/2023.
//

#pragma once

#include "AComponent.hpp"
#include "ComponentsType.hpp"

namespace Client {

    class IsSelected : public GameEngine::AComponent {
        public:
            size_t getComponentType() override;
    };

}