//
// Created by Clément Lagasse on 04/10/2023.
//

#pragma once

#include "TSQueue.hpp"
#include "Message.hpp"
#include "EventHandler.hpp"
#include "ISystem.hpp"

class NetworkInput : public GameEngine::ISystem {
    public:
        NetworkInput(std::shared_ptr<Network::TSQueue<std::shared_ptr<Network::OwnedMessage>>> &forwardQueue);
        void update(GameEngine::ComponentsContainer &componentsContainer,
                    GameEngine::EventHandler &eventHandler) override;
    private:
        std::shared_ptr<Network::TSQueue<std::shared_ptr<Network::OwnedMessage>>> _forwardQueue;
        static std::unordered_map<std::string, std::string> _actionEventMap;
};
