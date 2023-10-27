//
// Created by Clément Lagasse on 27/10/2023.
//

#include "SmoothMovementSystem.hpp"

void Client::SmoothMovementSystem::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto smoothingComp = GameEngine::ComponentsType::getComponentType("SmoothingMovement");
    auto entities = componentsContainer.getEntitiesWithComponent(smoothingComp);
    if (entities.empty()) {
        return;
    }
    for (auto entity: entities) {

    }
}