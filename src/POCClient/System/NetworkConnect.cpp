//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkConnect.hpp"

namespace Client {

    void NetworkConnect::update(GameEngine::ComponentsContainer &componentsContainer,
                                       GameEngine::EventHandler &eventHandler)
    {
        if (Network::Client::getInstance().isConnected())
            return;

        try {
            auto entityEndpoint = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("Endpoint"));
            auto endpointComponent = (componentsContainer.getComponent(entityEndpoint, GameEngine::ComponentsType::getComponentType("Endpoint")));
            if (endpointComponent.has_value()) {
                auto endpointPtr = std::dynamic_pointer_cast<Client::EndpointGame>(endpointComponent.value());
                int port = std::stoi(endpointPtr->_port);
                Network::Endpoint endpoint(endpointPtr->_host, port);
                std::cout << "Connecting to " << endpoint.ip << ":" << endpoint.port << std::endl;
                Network::Client::getInstance().connect("localhost", 4444);
                std::vector<size_t> ids = {};
                std::vector<std::any> args = {};
                std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("CONNECT", ids, "", args);
                eventHandler.queueEvent("SEND_NETWORK", message);
            }
        } catch (std::bad_any_cast &e) {
            std::cerr << "Error from NetworkClientConnect System " << e.what() << std::endl;
        }
    }
}
