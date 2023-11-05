/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkClientCharge
*/

#pragma once

#include "Server.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include <iostream>

namespace Server {

    class NetworkClientCharge : public GameEngine::ISystem {
        public:
            NetworkClientCharge() = default;
            void update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) override;
        private:
    };
}
