//
// Created by Clément Lagasse on 04/10/2023.
//

#include "NetworkOutput.hpp"

NetworkOutput::NetworkOutput(NetworkOutput::SystemType type) :_type(type)
{
}

void NetworkOutput::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    if (_type == CLIENT) {
        if (Network::Client::getInstance().isConnected()) {
            try {
                auto systemArg = eventHandler.getTriggeredEvent().second;
                auto iMessage = std::any_cast<std::shared_ptr<Network::IMessage>>(systemArg);
                Network::Client::getInstance().send(iMessage);
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from NetworkOutput System " << e.what() << std::endl;
            }
        }
    } else if (_type == SERVER) {
        size_t componentType = GameEngine::ComponentsType::getComponentType("NetworkClientId");
        auto eventArg = eventHandler.getTriggeredEvent().second;

        try {
            auto userMsgPtr = std::any_cast<std::shared_ptr<Network::UserMessage>>(eventArg);
            Network::Server::getInstance().sendClient(userMsgPtr->id, userMsgPtr->message);
            return ;
        } catch (const std::bad_any_cast&) {}

        try {
            auto usersMsgPtr = std::any_cast<std::shared_ptr<Network::UsersMessage>>(eventArg);
            Network::Server::getInstance().sendClients(usersMsgPtr->ids, usersMsgPtr->message);
        } catch (const std::bad_any_cast&) {}

        try {
            auto notUserMsgPtr = std::any_cast<std::shared_ptr<Network::NotUserMessage>>(eventArg);
            Network::Server::getInstance().sendAllClientsExcept(notUserMsgPtr->id, notUserMsgPtr->message);
            return ;
        } catch (const std::bad_any_cast&) {}

        try {
            auto allUserMsgPtr = std::any_cast<std::shared_ptr<Network::AllUsersMessage>>(eventArg);
            Network::Server::getInstance().sendAllClients(allUserMsgPtr->message);
            return ;
        } catch (const std::bad_any_cast&) {}
        std::cerr << "Error from NetworkOutput System: No message type found" << std::endl;
    }
}
