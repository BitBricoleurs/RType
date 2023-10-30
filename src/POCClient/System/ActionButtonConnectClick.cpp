//
// Created by Clément Lagasse on 25/10/2023.
//

#include "ActionButtonConnectClick.hpp"
#include "EndpointGame.hpp"

void Client::ActionButtonConnectClick::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto compTypeButtonConnect = GameEngine::ComponentsType::getComponentType("IsButtonConnect");
    auto buttonType = GameEngine::ComponentsType::getComponentType("ButtonComponent");

    std::vector<size_t > entities = componentsContainer.getEntitiesWithComponent(compTypeButtonConnect);

    if (entities.empty() || entities.size() > 1) {
        return;
    }
    auto mayComp = componentsContainer.getComponent(entities[0], buttonType);
    if (!mayComp.has_value()) {
        return;
    }
    auto buttonConnect = std::static_pointer_cast<RenderEngine::ButtonComponent>(mayComp.value());

    buttonConnect->rect1.x = buttonConnect->rect1.w * 2;
    size_t entityId = componentsContainer.createEntity();
    std::string host;
    std::string port;
    auto endpoint = std::make_shared<Client::EndpointGame>(host, port);
    componentsContainer.bindComponentToEntity(entityId, endpoint);
    eventHandler.scheduleEvent("NETWORK_CONNECT", 3, std::any());
}