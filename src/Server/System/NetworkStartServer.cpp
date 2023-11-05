//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkStartServer.hpp"

namespace Server {

    void NetworkStartServer::update(GameEngine::ComponentsContainer &componentsContainer,
                                    GameEngine::EventHandler &eventHandler)
    {
        Network::Server::getInstance().start();
        size_t entityId = componentsContainer.createEntity();
        std::shared_ptr<GameEngine::IComponent> gameState = std::make_shared<Utils::GameState>(Utils::GameState(Utils::GameState::State::WAITING));
        componentsContainer.bindComponentToEntity(entityId, gameState);
    }
}