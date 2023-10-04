//
// Created by alexandre on 03/10/23.
//

#include "ChargingBar.hpp"

void ChargingBar::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
{
{
    auto events = eventHandler.getTriggeredEvent();
    if (events.first == "SPACE_KEY_PRESSED") {
      _charge += 1;
      if (_charge > _maxCharge) {
        _charge = _maxCharge;
      }
      auto entities = componentsContainer.getEntitiesWithComponent(
          GameEngine::ComponentsType::getNewComponentType("IsChargingBar"));
      for (auto entity : entities) {
        auto eses = componentsContainer.getComponentsFromEntity(entity);
        for (const auto &optComp : eses) {
          if (optComp.has_value()) {
            auto aComp = std::dynamic_pointer_cast<GameEngine::AComponent>(optComp.value());
            if (aComp &&
                aComp->getComponentType() ==
                    GameEngine::ComponentsType::getNewComponentType("SpriteComponent")) {
              auto spriteComp =
                  std::dynamic_pointer_cast<GameEngine::SpriteComponent>(aComp);
              if (spriteComp) {
                auto currentRect = spriteComp->rect1;
                currentRect.w = _charge * 2;
                spriteComp->rect1 = currentRect;
              }
            }
          }
        }
      }
    } else if (events.first == "SPACE_KEY_RELEASED") {
      _charge -= 4;
      if (_charge < 0) {
        _charge = 0;
        eventHandler.queueEvent("STOP_UNCHARGING");
      }
      auto entities = componentsContainer.getEntitiesWithComponent(
          GameEngine::ComponentsType::getNewComponentType("IsChargingBar"));
      for (auto entity : entities) {
        auto eses = componentsContainer.getComponentsFromEntity(entity);
        for (const auto &optComp : eses) {
          if (optComp.has_value()) {
            auto aComp = std::dynamic_pointer_cast<GameEngine::AComponent>(optComp.value());
            if (aComp &&
                aComp->getComponentType() ==
                    GameEngine::ComponentsType::getNewComponentType("SpriteComponent")) {
              auto spriteComp =
                  std::dynamic_pointer_cast<GameEngine::SpriteComponent>(aComp);
              if (spriteComp) {
                auto currentRect = spriteComp->rect1;
                currentRect.w = _charge * 2;
                spriteComp->rect1 = currentRect;
              }
            }
          }
        }
      }
    }
  }
  }