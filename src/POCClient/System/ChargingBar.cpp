//
// Created by alexandre on 03/10/23.
//

#include "ChargingBar.hpp"

namespace Client {

    void ChargingBar::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
        auto events = eventHandler.getTriggeredEvent();
        auto isPlayerId = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("IsPlayer"));
        auto isPlayerOpt = componentsContainer.getComponent(isPlayerId, GameEngine::ComponentsType::getComponentType("IsPlayer"));
        if (isPlayerOpt.has_value()) {
            auto isPlayer = std::dynamic_pointer_cast<IsPlayer>(isPlayerOpt.value());
            if (events.first == "SPACE_KEY_PRESSED") {
                _charge += 1;
                if (_charge > _maxCharge) {
                    _charge = _maxCharge;
                }
                if (!shoot) {
                    shoot = true;
                    //eventHandler.unscheduleEvent("ShootSystem");
                }
            } else if (events.first == "SPACE_KEY_RELEASED") {
                if (shoot && endShoot) {
                    BulletTypeEntity type = BulletTypeEntity::PlayerBullet;
                    std::vector<size_t> ids = {};
                    std::vector<std::any> args = {static_cast<int>(type), _charge};
                    std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("CHARGE_SHOOT", ids, "INT", args);
                    eventHandler.queueEvent("SEND_NETWORK", message);
                    eventHandler.queueEvent("PLAY_SOUND", isPlayerId);
                    shoot = false;
                    endShoot = false;
                }
                _charge -= 4;
                if (_charge <= 0) {
                    endShoot = true;
                    _charge = 0;
                    shoot = false;
                    //auto IdCharge = std::make_tuple(isPlayer, _charge);
                    //eventHandler.scheduleEvent("ShootSystem", 20, IdCharge);
                    eventHandler.queueEvent("STOP_UNCHARGING");
                }
            }
        }
        auto entities = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getNewComponentType("IsChargingBar"));
        auto spriteOpt = componentsContainer.getComponent(entities, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        if (spriteOpt.has_value()) {
            auto sprite = std::dynamic_pointer_cast<RenderEngine::SpriteComponent>(spriteOpt.value());
            auto currentRect = sprite->rect1;
            currentRect.w = _charge * 2;
            sprite->rect1 = currentRect;
        }
    }

}