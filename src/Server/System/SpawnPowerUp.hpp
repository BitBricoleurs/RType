//
// Created by Bartosz on 10/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "PositionComponent2D.hpp"
#include "RectangleColliderComponent2D.hpp"
#include "AABBComponent2D.hpp"
#include "IsPowerUp.hpp"
#include "EntityFactory.hpp"
#include "isPowerUpPickUp.hpp"

namespace Server {
    class SpawnPowerUp : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    };
}