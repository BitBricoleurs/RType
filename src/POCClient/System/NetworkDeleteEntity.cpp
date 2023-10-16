//
// Created by Clément Lagasse on 14/10/2023.
//

#include "NetworkDeleteEntity.hpp"

void NetworkDeleteEntity::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    try {
            std::shared_ptr<Network::OwnedMessage> message;

            message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
            std::shared_ptr<Network::IMessage> IMessage = message->message;
            std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

            std::vector<size_t> ids = messageData->getIDs();
            std::vector<std::any> args = messageData->getArgs();

        if (ids.size() < 1)
            return;

        EntityFactory &entityFactory = EntityFactory::getInstance();
        size_t clientId = 0;
        for (auto &id : ids) {
            clientId = entityFactory.getClientId(id);
            eventHandler.queueEvent("KillEntity", clientId);
        }

    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from NetworkDeleteEntity System " << e.what() << std::endl;
    }
}