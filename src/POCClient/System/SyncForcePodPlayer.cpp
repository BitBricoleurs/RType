//
// Created by alexandre on 25/10/23.
//

#include "SyncForcePodPlayer.hpp"

void Client::SyncForcePodPlayer::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    try {
        std::shared_ptr<Network::OwnedMessage> message;
        try {
            message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkServerAccept System " << e.what() << std::endl;
            return ;
        }
        std::shared_ptr<Network::IMessage> IMessage = message->message;
        std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

        std::vector<size_t> ids = messageData->getIDs();
        std::vector<std::any> args = messageData->getArgs();

        if (ids.size() != 1)
                    return;

        int playerId = (std::any_cast<int>(args[0]));
        int forcePodId = (std::any_cast<int>(args[1]));
        auto entityIdForcePod = EntityFactory::getInstance().getClientId(forcePodId);
        auto clientPlayerId = EntityFactory::getInstance().getClientId(playerId);
        auto isPlayer = std::dynamic_pointer_cast<IsPlayer>(componentsContainer.getComponent(clientPlayerId, GameEngine::ComponentsType::getComponentType("IsPlayer")).value());
        isPlayer->entityIdForcePod = entityIdForcePod;
        auto forcePodVelocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(entityIdForcePod, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
        auto playerVelocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(componentsContainer.getComponent(clientPlayerId, GameEngine::ComponentsType::getComponentType("VelocityComponent")).value());
        forcePodVelocity->velocity = playerVelocity->velocity;
        }
        catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        }
}
