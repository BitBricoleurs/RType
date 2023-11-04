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

                if (ids.size() != 1 && (args.size() != (ids.size() * 5)))
                    return;
                EntityFactory  &factory = EntityFactory::getInstance();
                size_t entityId = 0;
                int arg_index = 0;
                for (auto id : ids ) {
                    auto typePowerUp = static_cast<PowerUpType>(std::any_cast<int>(args[arg_index]));
                    Utils::Vect2 pos(static_cast<float>(std::any_cast<int>(args[arg_index + 1])) / 1000, static_cast<float>(std::any_cast<int>(args[arg_index + 2])) / 1000);
                    Utils::Vect2 velocity(static_cast<float>(std::any_cast<int>(args[arg_index + 3])) / 1000, static_cast<float>(std::any_cast<int>(args[arg_index + 4])) / 1000);
                    entityId = Client::EntityFactory::getInstance().spawnPowerUp(componentsContainer, eventHandler, pos, velocity, typePowerUp);
                    factory.registerEntity(entityId, id);
                    arg_index += 5;
                }
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from createPowerUp System " << e.what() << std::endl;
            }

    }
}
