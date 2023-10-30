//
// Created by Bartosz on 10/9/23.
//

#include "PlayerHit.hpp"

void PlayerHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    try {
        auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);
        auto firstEntityOptPlayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));

        if (firstEntityOptPlayer.has_value()) {
            eventHandler.queueEvent("DAMAGE", firstEntity);
            eventHandler.queueEvent("PLAY_SOUND", firstEntity);
            componentsContainer.deleteEntity(secondEntity);
        } else {
            eventHandler.queueEvent("DAMAGE", secondEntity);
            eventHandler.queueEvent("PLAY_SOUND", secondEntity);
            componentsContainer.deleteEntity(firstEntity);
        }

    } catch (std::exception &e) {

    }
}