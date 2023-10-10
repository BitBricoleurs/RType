//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkStartServer.hpp"

void NetworkStartServer::update(GameEngine::ComponentsContainer &componentsContainer,
                                GameEngine::EventHandler &eventHandler)
{
    Network::Server::getInstance().start();
}