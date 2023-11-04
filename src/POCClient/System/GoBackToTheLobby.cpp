//
// Created by clagasse on 11/1/23.
//

#include "GoBackToTheLobby.hpp"

void Client::GoBackToTheLobby::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    try {
            std::shared_ptr<Network::OwnedMessage> message;

            message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
            std::shared_ptr<Network::IMessage> IMessage = message->message;
            std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

            std::vector<size_t> ids = messageData->getIDs();
            std::vector<std::any> args = messageData->getArgs();

            if (ids.size() != 0 && args.size() != 0)
                return;
            auto gameStateType = GameEngine::ComponentsType::getComponentType("GameState");
            size_t gameState = componentsContainer.getEntityWithUniqueComponent(gameStateType);
            auto mayComp = componentsContainer.getComponent(gameState, gameStateType);
            if (!mayComp.has_value())
                return;
            auto gameStateComp = std::static_pointer_cast<Utils::GameState>(mayComp.value());
            auto receivedGameState = static_cast<Utils::GameState::State>(std::any_cast<int>(args[0]));
            gameStateComp->_state = receivedGameState;
            std::cout << "Press 'Enter' to play again" << std::endl;
            eventHandler.queueEvent("CLEAR_NOTIF_LOSE");
            eventHandler.queueEvent("CLEAR_NOTIF_WIN");
            eventHandler.scheduleEvent("START_NOTIF_PLAY", 3, std::any(), 0);
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from goBackToTheLOOOOBY " << e.what() << std::endl;
        }
}