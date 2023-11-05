//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "Server.hpp"
#include "ComponentContainer.hpp"
#include "EventHandler.hpp"
#include "UserMessage.hpp"
#include "Message.hpp"
#include "NetworkClientId.hpp"
#include "EntityFactory.hpp"

namespace Server {

    class NetworkClientTimeout : public GameEngine::ISystem {
        public:
            NetworkClientTimeout() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:

    };

}
