//
// Created by Clément Lagasse on 02/11/2023.
//

#include "InitNotification.hpp"
#include "EntityFactory.hpp"

void Client::InitNotification::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    if (done)
        return;
    auto &factory = EntityFactory::getInstance();

    factory.createPlayNotification(componentsContainer, eventHandler);
    factory.createLoseNotification(componentsContainer, eventHandler);
    factory.createWinNotification(componentsContainer, eventHandler);
    done = true;
}