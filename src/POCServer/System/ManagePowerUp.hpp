//
// Created by alexandre on 30/10/23.
//

#pragma once

#include "ISystem.hpp"
#include "ComponentsType.hpp"
#include "EventHandler.hpp"
#include "IsPlayer.hpp"
#include "LoadConfig.hpp"
#include "NetworkClientId.hpp"
#include "Message.hpp"
#include "IMessage.hpp"
#include "UserMessage.hpp"

namespace Server {
    class ManagePowerUp : public GameEngine::ISystem {
        public:
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:
    };
}
