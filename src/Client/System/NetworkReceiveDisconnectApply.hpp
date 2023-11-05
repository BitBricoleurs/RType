//
// Created by Clément Lagasse on 06/10/2023.
//

#pragma once

#include "ISystem.hpp"
#include "Client.hpp"


namespace Client {

    class NetworkReceiveDisconnectApply : public GameEngine::ISystem {
        public:
            NetworkReceiveDisconnectApply() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:

    };
}
