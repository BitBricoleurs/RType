//
// Created by Clément Lagasse on 10/10/2023.
//

#include "CreateBulletSystem.hpp"

void CreateBulletSystem::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    BulletCreate bulletCreate;
    try {
        bulletCreate = std::any_cast<BulletCreate>(eventHandler.getTriggeredEvent().second);
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error from NetworkClientConnect System " << e.what() << std::endl;
    }
    // TODO: Factory create bullet

    std::vector<size_t> ids = {};
    std::vector<std::any> args = {};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("CREATED_BULLET", ids, "", args);
    std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
    eventHandler.queueEvent("SEND_NETWORK", allMessage);
}