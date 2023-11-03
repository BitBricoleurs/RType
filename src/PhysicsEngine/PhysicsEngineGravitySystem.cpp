//
// Created by Bartosz on 10/22/23.
//

#include "PhysicsEngineGravitySystem.hpp"


void GameEngine::PhysicsEngineGravitySystem::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    auto entities = componentsContainer.getEntitiesWithComponent(ComponentsType::getNewComponentType("GravitySystemComponent"));
    for (auto& entity : entities) {
        auto isOnGround1 = componentsContainer.getComponent(entity, ComponentsType::getNewComponentType("IsOnGroundComponent"));
        auto position1 = componentsContainer.getComponent(entity, ComponentsType::getNewComponentType("PositionComponent2D"));
        auto velocity1 = componentsContainer.getComponent(entity, ComponentsType::getNewComponentType("VelocityComponent"));
        auto gravity1 = componentsContainer.getComponent(entity, ComponentsType::getNewComponentType("GravityComponent"));
        auto isOnGround = std::dynamic_pointer_cast<PhysicsEngine::IsOnGroundComponent>(*isOnGround1);
        auto position = std::dynamic_pointer_cast<PhysicsEngine::PositionComponent2D>(*position1);
        auto velocity = std::dynamic_pointer_cast<PhysicsEngine::VelocityComponent>(*velocity1);
        auto gravity = std::dynamic_pointer_cast<PhysicsEngine::GravityComponent>(*gravity1);

        if (!isOnGround->onGround) {
            gravity->fallTime++;
            physicsEngine->applyGravity(*velocity, gravity->baseGravity, gravity->weight, gravity->fallTime);
        } else {
            gravity->fallTime = 0;
        }
    }
}