//
// Created by alexandre on 25/10/23.
//

#include "CreateForcePod.hpp"

namespace Client {
    void CreateForcePod::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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

                if (ids.size() != 1 && (args.size() != (ids.size() * 4)))
                    return;
                EntityFactory  &factory = EntityFactory::getInstance();

                size_t entityId = 0;
                int arg_index = 0;
                for (auto id : ids ) {
                    Utils::Vect2 pos(static_cast<float>(std::any_cast<int>(args[arg_index])) / 1000, static_cast<float>(std::any_cast<int>(args[arg_index + 1])) / 1000);
                    Utils::Vect2 velocity(static_cast<float>(std::any_cast<int>(args[arg_index + 2])) / 1000, static_cast<float>(std::any_cast<int>(args[arg_index + 3])) / 1000);
                    entityId = Client::EntityFactory::getInstance().spawnForcePod(componentsContainer, pos, velocity, eventHandler);
                    factory.registerEntity(entityId, id);
                }
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
            }

    }
}
