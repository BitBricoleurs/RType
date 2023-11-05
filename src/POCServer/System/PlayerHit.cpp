//
// Created by Bartosz on 10/9/23.
//

#include "PlayerHit.hpp"
#include "MobHit.hpp"
#include <vector>

namespace Server {
    void PlayerHit::applyDamage(const std::shared_ptr<Health>& hpComponent, size_t damageEntity, GameEngine::ComponentsContainer &componentsContainer) {
        auto damageComponentOpt = componentsContainer.getComponent(damageEntity, GameEngine::ComponentsType::getComponentType("Damage"));
        if (damageComponentOpt.has_value()) {
            auto damageComponent = std::static_pointer_cast<Damage>(damageComponentOpt.value());
            if (damageComponent)
                hpComponent->currentHealth -= damageComponent->damageValue;
        }
    }

    void PlayerHit::handleLifeLoss(size_t playerId, const std::shared_ptr<Health>& hpComponent, GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        hpComponent->lives -= 1;
        if (hpComponent->lives < 1) {
            auto playerGameStageOpt = componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("UserGameMode"));
            if (playerGameStageOpt.has_value()) {
                auto playerGameStage = std::static_pointer_cast<Utils::UserGameMode>(playerGameStageOpt.value());
                playerGameStage->_state = Utils::UserGameMode::State::DEAD;
            }
             sendDeathMessage(eventHandler, playerId);
        } else {
            hpComponent->currentHealth = hpComponent->maxHealth;
            flashNetwork(eventHandler, playerId);
        }
        std::vector<size_t> ids = {playerId};
        std::vector<std::any> args = {hpComponent->lives};
        lifeLostNetwork(eventHandler, ids, args);
    }

    void PlayerHit::handleOtherEntity(size_t otherEntity, GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        auto isBossOpt = componentsContainer.getComponent(otherEntity, GameEngine::ComponentsType::getComponentType("IsBoss"));
        auto isMobOpt = componentsContainer.getComponent(otherEntity, GameEngine::ComponentsType::getComponentType("IsMob"));
        auto scoreEntity = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("Score"));
        auto scoreComponentOpt = componentsContainer.getComponent(scoreEntity, GameEngine::ComponentsType::getComponentType("Score"));
        if (isBossOpt.has_value())
            return;
        if (isMobOpt.has_value() && scoreComponentOpt.has_value()) {
            auto mobHpComponentOpt = componentsContainer.getComponent(otherEntity, GameEngine::ComponentsType::getComponentType("Health"));
            if (mobHpComponentOpt.has_value()) {
                auto mobHpComponent = std::static_pointer_cast<Health>(mobHpComponentOpt.value());
                auto scoreComponent = std::static_pointer_cast<Score>(scoreComponentOpt.value());
                scoreComponent->score += mobHpComponent->maxHealth;
                updateScoreNetwork(eventHandler, scoreComponent->score);
            }
        }
        std::vector<size_t> ids = {otherEntity};
        killMobNetwork(eventHandler, ids);
        componentsContainer.deleteEntity(otherEntity);
    }

    void PlayerHit::killMobNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill)
    {
         std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", entitiesToKill, "", std::vector<std::any>{});
         std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
         eventHandler.queueEvent("SEND_NETWORK", allMessage);
    }

    void PlayerHit::lifeLostNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &players, std::vector<std::any> &args)
    {     
         std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("LIFE_LOST", players, "INT", args);
         std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
         eventHandler.queueEvent("SEND_NETWORK", allMessage);
    }

    void PlayerHit::flashNetwork(GameEngine::EventHandler &eventHandler, size_t entity)
    {
        std::vector<size_t> ids = {entity};
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("FLASH_ENTITY", ids, "", std::vector<std::any>{});
        std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allMessage);
    }

    void PlayerHit::updateScoreNetwork(GameEngine::EventHandler &eventHandler, size_t score)
    {
        std::vector<size_t> ids = {};
        int scoreInt = score;
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("UPDATE_SCORE", ids, "INT", std::vector<std::any>{scoreInt});
        std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allMessage);
    }

    void PlayerHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        try {
            auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);
            auto firstEntityOptPlayer = componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsPlayer"));

            size_t playerId, otherEntity;
            if (firstEntityOptPlayer.has_value()) {
                playerId = firstEntity;
                otherEntity = secondEntity;
            } else {
                playerId = secondEntity;
                otherEntity = firstEntity;
            }

            auto playerGameStateOpt = componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("UserGameMode"));
            if (!playerGameStateOpt.has_value())
                return;
            auto playerGameState = std::static_pointer_cast<Utils::UserGameMode>(playerGameStateOpt.value());
            if (playerGameState->_state != Utils::UserGameMode::State::ALIVE)
                return;

            auto isBulletOpt = componentsContainer.getComponent(otherEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
            auto hpComponentOpt = componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("Health"));
            auto lastHitComponentOpt = componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("CooldownHit"));
            if (hpComponentOpt.has_value() && lastHitComponentOpt.has_value()) {
                auto cooldownComponent = std::static_pointer_cast<CooldownHit>(lastHitComponentOpt.value());
                auto hpComponent = std::static_pointer_cast<Health>(hpComponentOpt.value());
                if (isBulletOpt.has_value()) {
                    auto isBullet = std::static_pointer_cast<IsBullet>(isBulletOpt.value());
                    if (isBullet->playerBullet)
                        return;
                }

                if (cooldownComponent->lastHit + std::chrono::milliseconds(90) > std::chrono::system_clock::now())
                    return;
                    
                cooldownComponent->lastHit = std::chrono::system_clock::now();

                applyDamage(hpComponent, otherEntity, componentsContainer);

                if (hpComponent->currentHealth <= 0)
                    handleLifeLoss(playerId, hpComponent, componentsContainer, eventHandler);
            }
            handleOtherEntity(otherEntity, componentsContainer, eventHandler);
        } catch (const std::bad_any_cast &e) {
            std::cerr << "Error in PlayerHit::update: " << e.what() << std::endl;
        }
    }
}

void Server::PlayerHit::sendDeathMessage(GameEngine::EventHandler &eventHandler, size_t entity)
{
    std::vector<size_t> ids = {entity};
    std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DEATH", ids, "", std::vector<std::any>{});
    std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
    eventHandler.queueEvent("SEND_NETWORK", allMessage);
}