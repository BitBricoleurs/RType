//
// Created by alexandre on 24/10/23.
//

#include "CreatePowerUp.hpp"

namespace Client {
    void CreatePowerUp::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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
                auto typePowerUp = static_cast<PowerUpType>(std::any_cast<int>(args[0]));
                EntityFactory  &factory = EntityFactory::getInstance();
                Utils::Vect2 pos = {0, 0};

                size_t entityId = 0;
                for (auto id : ids ) {
                    entityId = Client::EntityFactory::getInstance().spawnPowerUp(componentsContainer, eventHandler, typePowerUp);
                    factory.registerEntity(entityId, id);
                }
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
            }

    }
}
