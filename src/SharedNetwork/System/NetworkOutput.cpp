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
                Network::Client::getInstance().send(std::any_cast<std::shared_ptr<Network::IMessage>>(eventHandler.getTriggeredEvent().second));
            } catch (std::bad_any_cast &e) {
                std::cerr << "Error from NetworkOutput System " << e.what() << std::endl;
            }
        }
    } else if (_type == SERVER) {
        size_t componentType = GameEngine::ComponentsType::getComponentType("NetworkClientId");
        auto eventArg = eventHandler.getTriggeredEvent().second;

        try {
            auto userMsgPtr = std::any_cast<std::shared_ptr<Network::UserMessage>>(eventArg);
            auto mayComp = componentsContainer.getComponent(userMsgPtr->id, componentType);
            if (mayComp.has_value()) {
                unsigned int netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value())->id;
                Network::Server::getInstance().sendClient(netIdComp, userMsgPtr->message);
            }
            return ;
        } catch (const std::bad_any_cast&) {}

        try {
            auto usersMsgPtr = std::any_cast<std::shared_ptr<Network::UsersMessage>>(eventArg);
            std::vector<unsigned int> idsToBeSend = {};
            for (auto id : usersMsgPtr->ids) {
                auto mayComp = componentsContainer.getComponent(id, componentType);
                if (mayComp.has_value()) {
                    idsToBeSend.push_back(std::static_pointer_cast<NetworkClientId>(mayComp.value())->id);
                }
                return ;
            }
            Network::Server::getInstance().sendClients(idsToBeSend, usersMsgPtr->message);
        } catch (const std::bad_any_cast&) {}

        try {
            auto notUserMsgPtr = std::any_cast<std::shared_ptr<Network::NotUserMessage>>(eventArg);
            auto mayComp = componentsContainer.getComponent(notUserMsgPtr->id, componentType);
            if (mayComp.has_value()) {
                unsigned int netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value())->id;
                Network::Server::getInstance().sendAllClientsExcept(netIdComp, notUserMsgPtr->message);  // Fixed variable name from userMsgPtr to notUserMsgPtr
            }
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
