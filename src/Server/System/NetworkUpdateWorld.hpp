//
// Created by Clément Lagasse on 09/10/2023.
//

#pragma once

#include "Server.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "NetworkClientId.hpp"
#include "IsBullet.hpp"
#include "PositionComponent2D.hpp"
#include "VelocityComponent.hpp"
#include "MobUtils.hpp"
#include "PlayerUtils.hpp"
#include "BulletUtils.hpp"
#include "EntityFactory.hpp"

namespace Server {

    class NetworkUpdateWorld : public GameEngine::ISystem {
        public:
            NetworkUpdateWorld() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;

        private:

    };

}
