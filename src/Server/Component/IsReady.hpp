//
// Created by Clément Lagasse on 23/10/2023.
//

#pragma once

#include "ComponentsType.hpp"
#include "AComponent.hpp"

namespace Server {

    class IsReady : public GameEngine::AComponent {
    public:
       IsReady() = default;
       size_t getComponentType() override;
    };
}

