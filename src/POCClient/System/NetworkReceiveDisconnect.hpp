//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include "UserMessage.hpp"
#include "Message.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"

namespace Client {

    class NetworkReceiveDisconnect : public GameEngine::ISystem {
        public:
            NetworkReceiveDisconnect() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:
    };
}
