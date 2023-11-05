//
// Created by Theophilus Homawoo on 11/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "PositionComponent2D.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"
#include "SmoothingMovement.hpp"
#include "VelocityComponent.hpp"

namespace Client {
    class UpdatePosition : public GameEngine::ISystem {
    public:
        UpdatePosition() = default;
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
        bool isEntityMotionless(GameEngine::ComponentsContainer &componentsContainer, size_t entity);
        bool isEntityChangedPosition(GameEngine::ComponentsContainer &componentsContainer, size_t entit, Utils::Vect2 &targetPosition);
        bool isEntitySmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition);
        void trySmoothingPosition(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition);
        void tryRemovingSmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity);
        bool isVelocitySmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition);
        void smoothPosition(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition);
        bool isEntityPlayer(GameEngine::ComponentsContainer &componentsContainer, size_t entity);
        bool isEntitySmoothable(GameEngine::ComponentsContainer &componentsContainer, size_t entity);
    };
}