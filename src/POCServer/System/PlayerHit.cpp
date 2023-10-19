//
// Created by Bartosz on 10/9/23.
//

#include "PlayerHit.hpp"

namespace Server {

    void PlayerHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        try {
            auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);
            auto firstEntityOptPlayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));

            if (firstEntityOptPlayer.has_value()) {
                return;
                eventHandler.queueEvent("DAMAGE", firstEntity);
                std::vector<size_t> entities = {secondEntity};
                std::vector<std::any> args = {};
                std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("DELETED_ENTITY", entities, "", args);
                std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
                eventHandler.queueEvent("SEND_NETWORK", allMessage);
                componentsContainer.deleteEntity(secondEntity);
            } else {
                return;
                eventHandler.queueEvent("DAMAGE", secondEntity);
                std::vector<size_t> entities = {firstEntity};
                std::vector<std::any> args = {};
                std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("DELETED_ENTITY", entities, "", args);
                std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
                componentsContainer.deleteEntity(firstEntity);
            }

        } catch (std::exception &e) {

        }
    }
}
