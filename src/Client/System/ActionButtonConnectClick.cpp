//
// Created by Clément Lagasse on 25/10/2023.
//

#include "ActionButtonConnectClick.hpp"
#include "EndpointGame.hpp"
#include "InputText.hpp"

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
    size_t entityId = componentsContainer.createEntity(true);
    size_t menuIpEntity = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("IsMenuIp"));
    auto mayCompIp = componentsContainer.getComponent(menuIpEntity, GameEngine::ComponentsType::getComponentType("InputText"));
    size_t menuPortEntity = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("IsMenuPort"));
    auto mayCompPort = componentsContainer.getComponent(menuPortEntity, GameEngine::ComponentsType::getComponentType("InputText"));
    if (!mayCompIp.has_value() || !mayCompPort.has_value()) {
        return;
    }
    auto textIp = std::static_pointer_cast<Client::InputText>(mayCompIp.value());
    auto textPort = std::static_pointer_cast<Client::InputText>(mayCompPort.value());
    std::string host = textIp->getText();
    std::string port = textPort->getText();
    if (!isIpValid(host) || !isPortValid(port)) {
        return;
    }
    auto endpoint = std::make_shared<Client::EndpointGame>(host, port);
    componentsContainer.bindComponentToEntity(entityId, endpoint);
    eventHandler.queueEvent("gameEngineChangeScene", std::string("Game"));
}

bool Client::isIpValid(const std::string &ip)
{
    std::regex ipRegex("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$");
    return std::regex_match(ip, ipRegex);
}

bool Client::isPortValid(const std::string &port)
{
    std::regex portRegex("^[0-9]{1,5}$");
    return std::regex_match(port, portRegex);
}
