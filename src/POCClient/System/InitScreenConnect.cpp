//
// Created by Clément Lagasse on 24/10/2023.
//

#include "MenuNavigation.hpp"
#include "InitScreenConnect.hpp"
#include "EntityFactory.hpp"

void Client::InitScreenConnect::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    if (_done) {
        return;
    }
    auto &factory = Client::EntityFactory::getInstance();
    size_t entity = factory.createBackGroundConnect(componentsContainer);
    entity = factory.createMenuConnect(componentsContainer);
    size_t ip = factory.createInputIp(componentsContainer);
    size_t port = factory.createInputPort(componentsContainer);
    Client::MenuNavigationMethods::setMenuNavigation(ip, port, "RIGHT", componentsContainer);
    Client::MenuNavigationMethods::setMenuNavigation(port, ip, "LEFT", componentsContainer);
    entity = factory.createConnectButton(componentsContainer);
    eventHandler.queueEvent("UPDATE_SELECT");
    _done = true;
}