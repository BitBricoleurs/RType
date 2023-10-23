//
// Created by alexandre on 06/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "raylib.h"
#include "EventHandler.hpp"
#include "WindowInfoComponent.hpp"

namespace GameEngine {
    class ToggleFullScreen : public ISystem {
    public:
        ToggleFullScreen() = default;
        ~ToggleFullScreen() = default;

        void update(ComponentsContainer& componentsContainer, EventHandler& eventHandler) override;

    private:
    };
}
