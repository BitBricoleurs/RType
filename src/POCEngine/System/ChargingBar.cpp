//
// Created by alexandre on 03/10/23.
//

#include "ChargingBar.hpp"

void ChargingBar::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
    auto events = eventHandler.getTriggeredEvent();
    if (events.first == "SPACE_KEY_PRESSED") {
      _charge += 1;
      if (_charge > _maxCharge) {
        _charge = _maxCharge;
      }
      if (!shoot) {
          shoot = true;
      }
    } else if (events.first == "SPACE_KEY_RELEASED") {
        if (shoot) {
            auto entitiesChargeShoot = componentsContainer.getEntitiesWithComponent(GameEngine::ComponentsType::getNewComponentType("ChargeShoot"));
            for (auto entityIDShoot : entitiesChargeShoot) {
                auto chargeShootOpt = componentsContainer.getComponent(entityIDShoot, GameEngine::ComponentsType::getComponentType("ChargeShoot"));
                if (chargeShootOpt.has_value()) {
                    auto chargeShoot = std::dynamic_pointer_cast<ChargeShoot>(chargeShootOpt.value());
                    chargeShoot->charge = _charge;
                }
            }
            shoot = false;
        }
        _charge -= 4;
        if (_charge < 0) {
            _charge = 0;
            eventHandler.queueEvent("STOP_UNCHARGING");
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
