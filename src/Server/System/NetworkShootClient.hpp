//
// Created by Clément Lagasse on 13/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "Message.hpp"
#include "ComponentContainer.hpp"
#include "ComponentsType.hpp"
#include "NetworkClientId.hpp"
#include "Message.hpp"
#include "BulletUtils.hpp"
#include "Shooter.hpp"

namespace Server {

    class NetworkShootClient : public GameEngine::ISystem {
        public:
            NetworkShootClient() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:

    };

}
