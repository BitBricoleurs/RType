//
// Created by Clément Lagasse on 02/11/2023.
//

#include "InitNotification.hpp"
#include "EntityFactory.hpp"

void Client::InitNotification::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    if (done)
        return;
    auto &factoru = EntityFactory::getInstance();

    factoru.createPlayNotification(componentsContainer, eventHandler, {0, 0});

    done = true;
}