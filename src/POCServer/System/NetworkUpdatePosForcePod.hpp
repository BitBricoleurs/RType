//
// Created by alexandre on 26/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "Message.hpp"
#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"
#include "NetworkClientId.hpp"
#include "IsPlayer.hpp"
#include "PositionComponent2D.hpp"
#include "Shooter.hpp"
#include "VelocityComponent.hpp"
#include "EntityFactory.hpp"
#include "IsForcePod.hpp"

namespace Server {

    class NetworkUpdatePosForcePod : public GameEngine::ISystem {
        public:
            NetworkUpdatePosForcePod() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:
    };

}
