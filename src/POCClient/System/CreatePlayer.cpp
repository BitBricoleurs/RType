//
// Created by Clément Lagasse on 11/10/2023.
//

#include "CreatePlayer.hpp"

void CreatePlayer::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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

            PlayerNumber number = static_cast<PlayerNumber>(std::any_cast<int>(args[0]));
            EntityFactory  &factory = EntityFactory::getInstance();
            GameEngine::Vect2 pos = {0, 0};
            size_t entityId = factory.createNewStarship(componentsContainer, eventHandler, pos, number);

            factory.registerEntity(entityId, ids.front());

        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from UpdatePosition System " << e.what() << std::endl;
        }
}