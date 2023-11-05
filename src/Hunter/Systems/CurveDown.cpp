/*
** EPITECH PROJECT, 2023
** RType
** File description:
** CurveDown
*/

#include "CurveDown.hpp"

void CurveDown::update(GameEngine::ComponentsContainer &componentsContainer,
                       GameEngine::EventHandler &eventHandler) {
    try {
        size_t entityID = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);

        auto velocityOpt = componentsContainer.getComponent(
            entityID,
            GameEngine::ComponentsType::getComponentType("VelocityComponent"));

        if (velocityOpt.has_value()) {
            auto velocity = std::static_pointer_cast<PhysicsEngine::VelocityComponent>(
                velocityOpt.value());
            if (velocity->velocity.y == 0) {
                velocity->velocity.y = 0.1f;
            }
            velocity->velocity.y = velocity->velocity.y * 1.1f;
        }
    } catch (const std::bad_any_cast&) {
        std::cerr << "Cast error" << std::endl;
    }
}
