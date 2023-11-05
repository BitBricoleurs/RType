//
// Created by alexandre on 06/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "raylib.h"
#include "EventHandler.hpp"
#include "WindowInfoComponent.hpp"

namespace RenderEngine {
    class ToggleFullScreen : public GameEngine::ISystem {
    public:
        ToggleFullScreen() = default;
        ~ToggleFullScreen() = default;

        void update(GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler) override;

    private:
    };
}
