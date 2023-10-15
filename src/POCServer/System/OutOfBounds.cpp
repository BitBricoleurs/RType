//
// Created by Theophilus Homawoo on 15/10/2023.
//

#include "OutOfBounds.hpp"

void Server::OutOfBounds::update(GameEngine::ComponentsContainer & componentsContainer, GameEngine::EventHandler & eventHandler) {
    auto [eventName, eventData] = eventHandler.getTriggeredEvent();

    try {
        size_t entityID = std::any_cast<size_t>(eventData);

        auto positionOptional = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

        if (positionOptional.has_value()) {
            auto position = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOptional.value());

            if (position) {
                if (position->pos.x < 0 - _offset || position->pos.x > _width + _offset || position->pos.y < 0 - _offset || position->pos.y > _height + _offset) {
                    std::vector<size_t> entities = {entityID};
                    std::vector<std::any> args = {};
                    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("DELETED_ENTITY", entities, "", args);
                    std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
                    eventHandler.queueEvent("SEND_NETWORK", allMessage);
                    componentsContainer.deleteEntity(entityID);
                }
            }
        }
    } catch (std::bad_any_cast &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
