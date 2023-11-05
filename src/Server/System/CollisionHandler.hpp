//
// Created by Theophilus Homawoo on 08/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "isPowerUpPickUp.hpp"
#include "PositionComponent2D.hpp"
#include "Shooter.hpp"
#include "Message.hpp"
#include "IsForcePod.hpp"
#include "UserMessage.hpp"
#include "BossComponent.hpp"

namespace Server {

    class CollisionHandler : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;
    };
}
