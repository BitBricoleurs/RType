//
// Created by alexandre on 28/10/23.
//

#pragma once

#include "Server.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "NetworkClientId.hpp"
#include "VelocityComponent.hpp"
#include "IMessage.hpp"
#include "Shooter.hpp"
#include "IsPlayer.hpp"
#include "PositionComponent2D.hpp"
#include "EntityFactory.hpp"

namespace Server {

    class NetworkClientBlockWall : public GameEngine::ISystem {
        public:
            NetworkClientBlockWall() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;

        private:

    };
}
