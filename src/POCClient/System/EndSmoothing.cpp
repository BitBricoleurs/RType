//
// Created by Clément Lagasse on 28/10/2023.
//

#include "EndSmoothing.hpp"

void Client::EndSmoothing::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto smoothingType = GameEngine::ComponentsType::getComponentType("SmoothingMovement");

    auto entities = componentsContainer.getEntitiesWithComponent(smoothingType);
    if (entities.empty())
        return;
    auto positionType = GameEngine::ComponentsType::getComponentType("PositionComponent2D");
    auto velocityType = GameEngine::ComponentsType::getComponentType("VelocityComponent");

    for (auto &entity : entities) {
        auto maySmoothing = componentsContainer.getComponent(entity, smoothingType);
        auto mayPosition = componentsContainer.getComponent(entity, positionType);
        auto mayVelocity = componentsContainer.getComponent(entity, velocityType);
        if (!maySmoothing.has_value() || !mayPosition.has_value() || !mayVelocity.has_value())
            continue;
        auto smoothing = std::static_pointer_cast<Client::SmoothingMovement>(maySmoothing.value());
        auto position = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(mayPosition.value());
        auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(mayVelocity.value());

        std::cout <<"Target position :" << smoothing->_targetPosition.x << " " << smoothing->_targetPosition.y << std::endl;
        std::cout <<"Position :" << position->pos.x << " " << position->pos.y << std::endl;
        float dist = position->pos.distanceTo(smoothing->_targetPosition);
        if (dist <= 10) {
            componentsContainer.unbindComponentFromEntity(entity, smoothingType);
            velocity->velocity.x = 0;
            velocity->velocity.y = 0;
            std::cout << "End Smoothing" << std::endl;
        } else {
            if (isVelocitySmoothing(componentsContainer, entity) == false) {
                smoothPosition(componentsContainer, entity, smoothing->_targetPosition);}
        }
    }
}

void Client::EndSmoothing::smoothPosition(GameEngine::ComponentsContainer &componentsContainer, size_t entity, Utils::Vect2 &targetPosition)
{
    auto velocityComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
    auto positionComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    if (!velocityComponent.has_value() || !positionComponent.has_value())
        return;
    auto velComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityComponent.value());
    auto posComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionComponent.value());
    Utils::Vect2 directionToB = targetPosition - posComp->pos;
    Utils::Vect2 normalizedDirection = directionToB.normalize();
    int speed = 2;
    velComp->velocity = normalizedDirection * speed;
}

bool Client::EndSmoothing::isVelocitySmoothing(GameEngine::ComponentsContainer &componentsContainer, size_t entity)
{
    auto velocityComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("VelocityComponent"));
    auto positionComponent = componentsContainer.getComponent(entity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
    if (!velocityComponent.has_value() || !positionComponent.has_value())
        return false;
    auto velComp = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(velocityComponent.value());
    auto posComp = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(positionComponent.value());
    Utils::Vect2 directionToB = posComp->pos - velComp->velocity;
    Utils::Vect2 normalizedDirection = directionToB.normalize();
    Utils::Vect2 normalizedVelocity = velComp->velocity.normalize();
    return normalizedDirection.x == normalizedVelocity.x && normalizedDirection.y == normalizedVelocity.y;
}