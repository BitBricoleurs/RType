//
// Created by alexandre on 03/10/23.
//

#include "ChargingBar.hpp"
#include "Message.hpp"
#include "EntityFactory.hpp"

namespace Client {

    void ChargingBar::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler)
    {
    auto compTypeGameState = GameEngine::ComponentsType::getComponentType("GameState");
    auto compTypeIsPlayer = GameEngine::ComponentsType::getComponentType("IsPlayer");
    auto compTypeGameMode = GameEngine::ComponentsType::getComponentType("UserGameMode");
    std::vector<size_t> gameStateEntities = componentsContainer.getEntitiesWithComponent(compTypeGameState);
    size_t entityCheckPlayer = componentsContainer.getEntityWithUniqueComponent(compTypeIsPlayer);
    if (gameStateEntities.empty())
        return;
    auto mayCompGameMode = componentsContainer.getComponent(entityCheckPlayer, compTypeGameMode);
    auto compMay = componentsContainer.getComponent(gameStateEntities[0], compTypeGameState);
    if (!compMay.has_value() || !mayCompGameMode.has_value())
        return;
    auto gameMode = std::static_pointer_cast<Utils::UserGameMode>(mayCompGameMode.value());
    auto gameStateComp = std::static_pointer_cast<Utils::GameState>(compMay.value());
    if (gameStateComp->_state != Utils::GameState::State::RUNNING || gameMode->_state != Utils::UserGameMode::State::ALIVE)
        return;
    auto events = eventHandler.getTriggeredEvent();
    auto isPlayerId = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("IsPlayer"));
    auto isPlayerOpt = componentsContainer.getComponent(isPlayerId, GameEngine::ComponentsType::getComponentType("IsPlayer"));

    if (isPlayerOpt.has_value()) {
        auto isPlayer = std::static_pointer_cast<IsPlayer>(isPlayerOpt.value());
        auto spriteChargeOpt = componentsContainer.getComponent(isPlayer->entityIdChargeAnimation, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
        if (events.first == "SPACE_KEY_PRESSED") {
            _charge += 1;
            if (_charge > _maxCharge) {
                _charge = _maxCharge;
            }
            if (!shoot) {
                shoot = true;
                if (spriteChargeOpt.has_value()) {
                    auto spriteCharge = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteChargeOpt.value());
                    spriteCharge->isVisible = true;
                }
                size_t serverId = EntityFactory::getInstance().getServerId(isPlayerId);
                std::vector<std::any> args = {1, static_cast<int>(serverId)};
                std::vector<size_t> ids = {};
                std::shared_ptr<Network::IMessage> message = std::make_shared<Network::Message>("CHARGE", ids, "INT", args);
                eventHandler.queueEvent("SEND_NETWORK", message);
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
                if (spriteChargeOpt.has_value()) {
                    auto spriteCharge = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteChargeOpt.value());
                    spriteCharge->isVisible = false;
                }
                size_t serverId = EntityFactory::getInstance().getServerId(isPlayerId);
                std::vector<std::any> args2 = {0, static_cast<int>(serverId)};
                std::shared_ptr<Network::IMessage> nmessage = std::make_shared<Network::Message>("CHARGE", ids, "INT", args2);
                eventHandler.queueEvent("SEND_NETWORK", nmessage);
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
    auto entities = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("IsChargingBar"));
    auto spriteOpt = componentsContainer.getComponent(entities, GameEngine::ComponentsType::getComponentType("SpriteComponent"));
    if (spriteOpt.has_value()) {
        auto sprite = std::static_pointer_cast<RenderEngine::SpriteComponent>(spriteOpt.value());
        auto currentRect = sprite->rect1;
        currentRect.w = _charge * 2;
        sprite->rect1 = currentRect;
    }
    }
}