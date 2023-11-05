//
// Created by Clément Lagasse on 05/11/2023.
//

#include "DeletePowerUp.hpp"

void Server::DeletePowerUp::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto paralaxCompType = GameEngine::ComponentsType::getComponentType("IsPower");

    auto entities = componentsContainer.getEntitiesWithComponent(paralaxCompType);
    std::vector<size_t> entitiesToDelete;
    for (auto &entity : entities) {
        componentsContainer.deleteEntity(entity);
        entitiesToDelete.push_back(entity);
    }
    std::vector<std::any> args = {};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", entitiesToDelete, "", args);
    std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
    eventHandler.queueEvent("SEND_NETWORK", allMessage);
}