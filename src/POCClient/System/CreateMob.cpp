//
// Created by Clément Lagasse on 11/10/2023.
//

#include "CreateMob.hpp"

void CreateMob::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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
            if (args.size() != 1)
                return;
            MobType typeMob = static_cast<MobType>(std::any_cast<int>(args[0]));
            EntityFactory  &factory = EntityFactory::getInstance();
            Utils::Vect2 pos = {0, 0};

            size_t entityId = 0;
            for (auto id : ids ) {
                if (typeMob == MobType::CANCER) {
                    entityId = factory.spawnCancerMob(componentsContainer, eventHandler, pos, 0);
                } else if (typeMob == MobType::PATAPATA) {
                    entityId = factory.spawnPataPataMob(componentsContainer, eventHandler, pos, 0);
                } else {
                    entityId = factory.spawnBugMob(componentsContainer, eventHandler, pos, 0);
                }
                factory.registerEntity(entityId, id);
            }
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        }
}