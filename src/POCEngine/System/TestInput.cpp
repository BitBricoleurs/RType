//
// Created by alexandre on 04/10/23.
//

#include "TestInput.hpp"

void TestInput::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto stopSys = std::make_shared<ForcePodSpawn>();
    float posY = 500;
    eventHandler.queueEvent("ForcePodSpawn", posY);
}
