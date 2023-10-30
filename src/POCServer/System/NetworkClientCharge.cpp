/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkClientCharge
*/

#include "NetworkClientCharge.hpp"
#include <cstddef>

void Server::NetworkClientCharge::update(GameEngine::ComponentsContainer &componentsContainer,
                        GameEngine::EventHandler &eventHandler) {

    std::shared_ptr<Network::OwnedMessage> message;

    try {
        message = std::any_cast<std::shared_ptr<Network::OwnedMessage>>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from NetworkClientCharge System " << e.what() << std::endl;
        return ;
    }

    // resending the message to all clients
    std::shared_ptr<Network::IMessage> IMessage = message->message;
    std::shared_ptr<Network::Message> messageData = std::make_shared<Network::Message>(IMessage->getMessage());

    std::vector<std::any> args;
    for (auto &arg : messageData->getArgs()) {
        try {
            args.push_back(std::any_cast<int>(arg));
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkMoveClient System Float" << e.what() << std::endl;
            return;
        }
    }
    std::vector<size_t> ids = {};
    
    std::shared_ptr<Network::Message> chargeMessage = std::make_shared<Network::Message>("CHARGE", ids, "INT", args);
    std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(chargeMessage);
    eventHandler.queueEvent("SEND_NETWORK", allMessage);
}