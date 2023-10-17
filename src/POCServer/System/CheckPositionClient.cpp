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
        auto position = componentsContainer.getComponent(entity, positionComp);
        if (position.has_value()) {
            auto positionComp = std::static_pointer_cast<GameEngine::PositionComponent2D>(position.value());
        }
    }
}