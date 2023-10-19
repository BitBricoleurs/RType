//
// Created by Clément Lagasse on 13/10/2023.
//

#include "CheckPositionClient.hpp"

void CheckPositionClient::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    std::vector<size_t > ids = {};

    auto playerComp = GameEngine::ComponentsType::getComponentType("IsPlayer");
    auto positionComp = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
    auto shootComp = GameEngine::ComponentsType::getComponentType("Shooter");

    auto entities = componentsContainer.getEntitiesWithComponent(playerComp);
    for (auto &entity : entities) {
        auto position = componentsContainer.getComponent(entity, positionComp);
        auto shooter = componentsContainer.getComponent(entity, shootComp);
        if (position.has_value()) {
            auto positionComp = std::static_pointer_cast<GameEngine::PositionComponent2D>(position.value());
            std::cout << "Player num: "<< entity << "X: " << positionComp->pos.x << " Y: " << positionComp->pos.y << std::endl;
            if (shooter.has_value()) {
                auto shooterComp = std::static_pointer_cast<Shooter>(shooter.value());
                std::cout << "Player shoot num: "<< entity << "X: " << shooterComp->shootPosition.x << " Y: " << shooterComp->shootPosition.y << std::endl;
            }
        }
    }
}