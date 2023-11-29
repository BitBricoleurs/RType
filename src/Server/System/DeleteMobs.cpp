//
// Created by clagasse on 11/1/23.
//

#include "DeleteMobs.hpp"

void Server::DeleteMobs::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto paralaxCompType = GameEngine::ComponentsType::getComponentType("IsMob");

    auto entities = componentsContainer.getEntitiesWithComponent(paralaxCompType);
    std::vector<size_t> entitiesToDelete;
    for (auto &entity : entities) {
        auto isLastMobOpt = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("IsLastMob"));
        if (isLastMobOpt.has_value()) {
            eventHandler.queueEvent("WIN_LEVEL");
        }
        componentsContainer.deleteEntity(entity);
        entitiesToDelete.push_back(entity);
    }
    std::vector<std::any> args = {};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", entitiesToDelete, "", args);
    std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
    eventHandler.queueEvent("SEND_NETWORK", allMessage);
}