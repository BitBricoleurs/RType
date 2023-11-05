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

        auto isPlayerType = GameEngine::ComponentsType::getComponentType("IsPlayer");
        auto velType = GameEngine::ComponentsType::getComponentType("VelocityComponent");

        auto playerOpt = componentsContainer.getComponent(clientPlayerId, isPlayerType);
        auto forcePodOpt = componentsContainer.getComponent(entityIdForcePod, velType);
        auto velOpt = componentsContainer.getComponent(clientPlayerId, velType);

        if (!playerOpt.has_value() || !forcePodOpt.has_value() || !velOpt.has_value())
            return;


        auto isPlayer = std::static_pointer_cast<IsPlayer>(playerOpt.value());
        isPlayer->entityIdForcePod = entityIdForcePod;
        auto forcePodVelocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(forcePodOpt.value());
        auto playerVelocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velOpt.value());
        forcePodVelocity->velocity = playerVelocity->velocity;
        }
        catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        }
}
