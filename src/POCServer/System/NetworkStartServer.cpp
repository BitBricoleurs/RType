//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkStartServer.hpp"

NetworkStartServer::NetworkStartServer(std::shared_ptr<Network::Server> &server) : _server(server)
{
}

void NetworkStartServer::update(GameEngine::ComponentsContainer &componentsContainer,
                                GameEngine::EventHandler &eventHandler)
{
    _server->start();
}