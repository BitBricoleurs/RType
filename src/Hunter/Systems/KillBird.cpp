/*
** EPITECH PROJECT, 2023
** RType
** File description:
** KillBird
*/

#include "KillBird.hpp"

void KillBird::update(GameEngine::ComponentsContainer &componentsContainer,
                      GameEngine::EventHandler &eventHandler) {
    try {
        size_t entityID = std::any_cast<size_t>(eventHandler.getTriggeredEvent().second);

        auto buttonOpt = componentsContainer.getComponent(
            entityID,
            GameEngine::ComponentsType::getComponentType("ButtonComponent"));

        if (buttonOpt.has_value()) {
            auto button = std::static_pointer_cast<RenderEngine::ButtonComponent>(
                buttonOpt.value());
            button->clickEvent = "";
        }

        //   auto velocityOpt = componentsContainer.getComponent(
        //       entityID,
        //       GameEngine::ComponentsType::getComponentType("VelocityComponent"));

        //   if (velocityOpt.has_value()) {
        //     auto velocity =
        //     std::dynamic_pointer_cast<GameEngine::VelocityComponent>(
        //         velocityOpt.value());
        //     velocity->velocity.x = 0;
        //     velocity->velocity.y = 0;
        //   }
        eventHandler.queueEvent("PLAY_SOUND", entityID);

        eventHandler.scheduleEvent("animateDeath", 5, entityID);
        eventHandler.scheduleEvent("curveDown", 1, entityID);
        eventHandler.queueEvent("updateScore", 1);
    } catch (const std::bad_any_cast&) {
        std::cerr << "Cast error in KillBird::update" << std::endl;
    }
}
