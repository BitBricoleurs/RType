//
// Created by clagasse on 11/1/23.
//

#include "SpawnEntityEvent.hpp"

void Server::SpawnEntityChangeLevel::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    spawnEntity->changeLevel();
}

void Server::SpawnEntityResetLevel::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    spawnEntity->resetCurrentLevel();
}