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
        size_t componentType = GameEngine::ComponentsType::getComponentType("NetworkClientId");
        try {
            if (auto userMsgPtr = std::any_cast<std::shared_ptr<Network::UserMessage>>(eventHandler.getTriggeredEvent().second)) {
                auto mayComp = componentsContainer.getComponent(userMsgPtr->id, componentType);
                if (!mayComp.has_value())
                    return;
                unsigned int netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value())->id;
                _server->sendClient(netIdComp, userMsgPtr->message);
            }
            else if (auto usersMsgPtr = std::any_cast<std::shared_ptr<Network::UsersMessage>>(eventHandler.getTriggeredEvent().second)) {
                std::vector<unsigned int> idsToBeSend = {};
                for (auto id : usersMsgPtr->ids) {
                    auto mayComp = componentsContainer.getComponent(id, componentType);
                    if (!mayComp.has_value())
                        continue;
                    idsToBeSend.push_back(std::static_pointer_cast<NetworkClientId>(mayComp.value())->id);
                }
                _server->sendClients(idsToBeSend, usersMsgPtr->message);
            }
            else if (auto notUserMsgPtr = std::any_cast<std::shared_ptr<Network::NotUserMessage>>(eventHandler.getTriggeredEvent().second)) {
                auto mayComp = componentsContainer.getComponent(notUserMsgPtr->id, componentType);
                if (!mayComp.has_value())
                    return;
                unsigned int netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value())->id;
                _server->sendAllClientsExcept(netIdComp, userMsgPtr->message);
            }
            else if (auto allUserMsgPtr = std::any_cast<std::shared_ptr<Network::AllUsersMessage>>(eventHandler.getTriggeredEvent().second)) {
                _server->sendAllClients(allUserMsgPtr->message);
            }
            else {
                throw std::runtime_error("Unknown message type in eventHandler.getTriggeredEvent().second");
            }
        } catch (const std::exception &e) {
            std::cerr << "Error from NetworkOutput System " << e.what() << std::endl;
        }
    }
}
