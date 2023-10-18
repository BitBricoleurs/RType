//
// Created by Clément Lagasse on 13/10/2023.
//

#include "CheckPositionClient.hpp"

void CheckPositionClient::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    std::vector<size_t > ids = {};

    auto playerComp = GameEngine::ComponentsType::getComponentType("IsPlayer");
    auto positionComp = GameEngine::ComponentsType::getComponentType("PositionComponent2D");

    auto entities = componentsContainer.getEntitiesWithComponent(playerComp);
    for (auto &entity : entities) {
        auto positionOpt = componentsContainer.getComponent(entity, positionComp);
        if (positionOpt.has_value()) {
            auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionOpt.value());
        }
    }
}
