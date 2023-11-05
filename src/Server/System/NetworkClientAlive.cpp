//
// Created by Clément Lagasse on 27/10/2023.
//

#include "NetworkClientAlive.hpp"

void Server::NetworkClientAlive::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    // Nothing to do cause the NetworkLib already register it but in case the event is stored after each tick.
}