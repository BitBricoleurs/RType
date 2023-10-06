//
// Created by Clément Lagasse on 04/10/2023.
//

#include "NetworkOutput.hpp"

NetworkOutput::NetworkOutput(std::shared_ptr<Network::Client> &client) : _client(client), _type(CLIENT)
{
}

NetworkOutput::NetworkOutput(std::shared_ptr<Network::Server> &server) : _server(server), _type(SERVER)
{
}

void NetworkOutput::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    if (_type == CLIENT) {
        if (_client->isConnected()) {
            try {
            _client->send(std::any_cast<std::shared_ptr<Network::IMessage>>(eventHandler.getTriggeredEvent().second));
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from NetworkOutput System " << e.what() << std::endl;
            }
        }
    } else if (_type == SERVER) {
        try {
            if (auto userMsgPtr = std::any_cast<std::shared_ptr<Network::UserMessage>>(eventHandler.getTriggeredEvent().second)) {
                // TODO: Look into Component for find the real Network ID and not the Entity ID
                _server->sendClient(userMsgPtr->id, userMsgPtr->message);
            }
            else if (auto usersMsgPtr = std::any_cast<std::shared_ptr<Network::UsersMessage>>(eventHandler.getTriggeredEvent().second)) {
                for (auto id : usersMsgPtr->ids) {
                    // TODO: Look into Component for find the real Network ID and not the Entity ID
                    _server->sendClient(id, usersMsgPtr->message);
                }
            }
            else if (auto notUserMsgPtr = std::any_cast<std::shared_ptr<Network::NotUserMessage>>(eventHandler.getTriggeredEvent().second)) {
                // TODO: Look into Component for find the real Network ID and not the Entity ID
                _server->sendAllClientsExcept(notUserMsgPtr->id, notUserMsgPtr->message);
            }
            else {
                throw std::runtime_error("Unknown message type in eventHandler.getTriggeredEvent().second");
            }
        } catch (const std::exception &e) {
            std::cerr << "Error from NetworkOutput System " << e.what() << std::endl;
        }
    }
}
