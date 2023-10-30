//
// Created by Clément Lagasse on 06/10/2023.
//

#include "NetworkClientTimeout.hpp"

namespace Server {

    void NetworkClientTimeout::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
            Network::TSQueue<unsigned int> &timedOutQueue = Network::Server::getInstance().getTimeOutClients();

            while (!timedOutQueue.empty()) {
                unsigned int netInterfaceId = timedOutQueue.popBack();
                size_t componentType = GameEngine::ComponentsType::getComponentType("NetworkClientId");
                auto entitiesPlayers = componentsContainer.getEntitiesWithComponent(componentType);
                EntityFactory &factory = EntityFactory::getInstance();
                for (auto &entity : entitiesPlayers) {
                    auto mayComp = componentsContainer.getComponent(entity, componentType);
                    if (!mayComp.has_value())
                        continue;
                    auto netIdComp = std::static_pointer_cast<NetworkClientId>(mayComp.value());
                    if (netIdComp->id == netInterfaceId) {
                        Network::Server::getInstance().disconnectClient(netIdComp->id);
                        componentsContainer.deleteEntity(entity);
                        factory.unregisterPlayer(entity);
                        std::vector<size_t> ids = {entity};
                        std::vector<std::any> args = {};
                        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", ids, "", args);
                        std::shared_ptr<Network::AllUsersMessage> notMessage = std::make_shared<Network::AllUsersMessage>(message);
                        eventHandler.queueEvent("SEND_NETWORK", notMessage);
                }
            }
        }
    }
}
