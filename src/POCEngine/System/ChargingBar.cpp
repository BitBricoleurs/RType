//
// Created by alexandre on 03/10/23.
//

#include "ChargingBar.hpp"

void ChargingBar::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto events = eventHandler.getTriggeredEvent();
    auto isPlayerId = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getComponentType("IsPlayer"));

    for (auto &entityId : isPlayerId) {
        auto isPlayerOpt = componentsContainer.getComponent(entityId, GameEngine::ComponentsType::getComponentType("IsPlayer"));
        if (isPlayerOpt.has_value()) {
            auto isPlayer = std::dynamic_pointer_cast<IsPlayer>(isPlayerOpt.value());
            auto positionOpt = componentsContainer.getComponent(entityId, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
            auto spriteChargeOpt = componentsContainer.getComponent(isPlayer->entityIdChargeAnimation, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
            auto positionChargeOpt = componentsContainer.getComponent(isPlayer->entityIdChargeAnimation, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
            auto shooterOpt = componentsContainer.getComponent(entityId, GameEngine::ComponentsType::getComponentType("Shooter"));
            if(positionOpt.has_value() && spriteChargeOpt.has_value() && shooterOpt.has_value() && positionChargeOpt.has_value()) {
                auto spriteCharge = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteChargeOpt.value());
                auto position = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionOpt.value());
                auto shooter = std::dynamic_pointer_cast<Shooter>(shooterOpt.value());
                auto chargePos = std::dynamic_pointer_cast<GameEngine::PositionComponent2D>(positionChargeOpt.value());
                if (events.first == "SPACE_KEY_PRESSED") {
                  _charge += 1;
                  if (_charge > _maxCharge) {
                    _charge = _maxCharge;
                  }
                  //if (!shoot) {
                  GameEngine::Vect2 shootingPosition(position->pos.x + shooter->shootPosition.x, position->pos.y + shooter->shootPosition.y - 30);
                  chargePos->pos = shootingPosition;
                  spriteCharge->isVisible = true;
                  shoot = true;
                  eventHandler.unscheduleEvent("ShootSystem");
                  //}
                } else if (events.first == "SPACE_KEY_RELEASED") {
                    if (shoot && endShoot) {
                        auto IdCharge = std::make_tuple(entityId, _charge);
                        eventHandler.queueEvent("ShootSystem", IdCharge);
                        spriteCharge->isVisible = false;
                        shoot = false;
                        endShoot = false;
                    }
                    _charge -= 4;
                    if (_charge <= 0) {
                        endShoot = true;
                        _charge = 0;
                        shoot = false;
                        auto IdCharge = std::make_tuple(entityId, 0);
                        eventHandler.scheduleEvent("ShootSystem", 20, IdCharge);
                        eventHandler.queueEvent("STOP_UNCHARGING");
                    }
                }
            }
        }
    }
    auto entities = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("IsChargingBar"));
    for (auto entityID : entities) {
        auto spriteOpt = componentsContainer.getComponent(entityID, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        if (spriteOpt.has_value()) {
            auto sprite = std::dynamic_pointer_cast<GameEngine::SpriteComponent>(spriteOpt.value());
            auto currentRect = sprite->rect1;
            currentRect.w = _charge * 2;
            sprite->rect1 = currentRect;
        }
    }
}
