//
// Created by Clément Lagasse on 27/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "PositionComponent2D.hpp"
#include "SpriteComponent.hpp"
#include "SmoothingMovement.hpp"

namespace Client {
    class SmoothMovementSystem : public GameEngine::ISystem {
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}
