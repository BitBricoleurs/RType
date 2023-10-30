//
// Created by Clément Lagasse on 28/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "VelocityComponent.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"
#include "SmoothingMovement.hpp"
#include "VelocityComponent.hpp"
#include "PositionComponent2D.hpp"

namespace Client {

    class EndSmoothing : public GameEngine::ISystem {
    public:
        EndSmoothing() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;

        bool isVelocitySmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity);
        void smoothPosition(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition);
    };

}
