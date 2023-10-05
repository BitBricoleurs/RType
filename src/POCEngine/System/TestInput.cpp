//
// Created by alexandre on 04/10/23.
//

#include "TestInput.hpp"

void TestInput::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto anyEvent = eventHandler.getTriggeredEvent();
    if (anyEvent.first == "CONTROL_KEY_PRESSED") {
        auto stopSys = std::make_shared<ForcePodSpawn>();
        float posY = 500;
        eventHandler.queueEvent("ForcePodSpawn", posY);
    } else if (anyEvent.first == "ENTER_KEY_PRESSED") {
        auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsPlayer"));
        for (const auto& entityID : entities) {
            eventHandler.queueEvent("ForcePodFix", entityID);
            return;
        }
    }
}
