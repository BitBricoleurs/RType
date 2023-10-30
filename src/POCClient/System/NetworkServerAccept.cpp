//
// Created by Clément Lagasse on 08/10/2023.
//

#include "NetworkServerAccept.hpp"
#include "UserGameMode.hpp"

namespace Client {

    void NetworkServerAccept::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
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

                if (ids.size() != 1 || !(args.size() == 6 || args.size() == 2))
                    return;

                size_t entityId = 0;
                EntityFactory  &factory = EntityFactory::getInstance();
                auto number = static_cast<PlayerNumber>(std::any_cast<int>(args[0]));
                auto gameMode = static_cast<Utils::UserGameMode::State>(std::any_cast<int>(args[1]));
                auto compUserGameMode = std::make_shared<Utils::UserGameMode>(gameMode);
                if (number == PlayerNumber::Spectator) {
                    entityId = componentsContainer.createEntity();
                } else {
                    Utils::Vect2 pos(static_cast<float>(std::any_cast<int>(args[1])) / 1000, static_cast<float>(std::any_cast<int>(args[2])) / 1000);
                    entityId = factory.createNewPlayer(componentsContainer, eventHandler, pos, number);
                }
                componentsContainer.bindComponentToEntity(entityId, compUserGameMode);
                auto gameState = std::make_shared<Utils::GameState>(Utils::GameState::State::WAITING);
                componentsContainer.bindComponentToEntity(entityId, gameState);
                factory.registerEntity(entityId, ids.front());
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkServerAccept System " << e.what() << std::endl;
        }
    }
}
