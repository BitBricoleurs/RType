/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SyncChargePos
*/

#include "SyncChargePos.hpp"

void SyncChargePos::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
    auto triggeredEvent = eventHandler.getTriggeredEvent().first;
    auto chargeAnimations = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("ChargeShoot"));

    for (auto &chargeId : chargeAnimations) {
        auto chargeOpt = componentsContainer.getComponent(chargeId, GameEngine::ComponentsType::getComponentType("ChargeShoot"));
        auto spriteOpt = componentsContainer.getComponent(chargeId, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        auto positionOpt = componentsContainer.getComponent(chargeId, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));

        if (chargeOpt.has_value() && spriteOpt.has_value() && positionOpt.has_value()) {
            auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOpt.value());
            auto charge = std::dynamic_pointer_cast<ChargeShoot>(chargeOpt.value());
            auto position = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOpt.value());
            auto playerShootOpt = componentsContainer.getComponent(charge->player, GameEngine::ComponentsType::getComponentType("Shooter"));
            if (playerShootOpt.has_value()) {
                auto shooter = std::dynamic_pointer_cast<Shooter>(playerShootOpt.value());
                if (strcmp(triggeredEvent.c_str(), "SPACE_KEY_RELEASED") == 0) {
                    if (shoot) {
                        eventHandler.queueEvent("ShootSystem", charge->player);
                        sprite->isVisible = false;
                        shoot = false;
                        eventHandler.scheduleEvent("ShootSystem", 20, charge->player);
                    }
                } else if (strcmp(triggeredEvent.c_str(), "STOP_UNCHARGING") == 0) {
                    return;
                } else {
                    eventHandler.unscheduleEvent("ShootSystem");
                    auto playerPosOpt = componentsContainer.getComponent(charge->player, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
                    if (playerPosOpt.has_value()) {
                        auto posPlayer = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(playerPosOpt.value());
                        GameEngine::Vect2 shootingPosition(posPlayer->pos.x + shooter->shootPosition.x, posPlayer->pos.y + shooter->shootPosition.y - 30);
                        position->pos = shootingPosition;
                        sprite->isVisible = true;
                        shoot = true;
                    }
                }
            }
        }
    }
}
