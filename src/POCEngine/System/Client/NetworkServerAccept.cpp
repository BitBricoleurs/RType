//
// Created by Clément Lagasse on 08/10/2023.
//

#include "NetworkServerAccept.hpp"

void NetworkServerAccept::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    size_t entityId = componentsContainer.createEntity();
    componentsContainer.bindComponentToEntity(entityId, std::make_shared<IsPlayer>(0));
}