//
// Created by Bartosz on 10/9/23.
//

#include "PlayerHit.hpp"
#include "MobHit.hpp"

namespace Server {

    void MobHit::applyDamage(const std::shared_ptr<Health>& hpComponent, size_t damageEntity, GameEngine::ComponentsContainer &componentsContainer) {
        auto damageComponentOpt = componentsContainer.getComponent(damageEntity, GameEngine::ComponentsType::getComponentType("Damage"));
        if (damageComponentOpt.has_value()) {
            auto damageComponent = std::dynamic_pointer_cast<Damage>(damageComponentOpt.value());
            if (damageComponent)
                hpComponent->currentHealth -= damageComponent->damageValue;
        }
    }

    void MobHit::handleLifeLoss(size_t playerId, const std::shared_ptr<Health>& hpComponent, GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        hpComponent->lives -= 1;
        if (hpComponent->lives <= 0) {
            auto playerGameStageOpt = componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("UserGameMode"));
            if (playerGameStageOpt.has_value()) {
                auto playerGameStage = std::static_pointer_cast<UserGameMode>(playerGameStageOpt.value());
                playerGameStage->_state = UserGameMode::State::DEAD;
            }
        } else {
            hpComponent->currentHealth = hpComponent->maxHealth;
            flashMobNetwork(eventHandler, playerId);
        }
        std::vector<size_t> ids = {playerId};
        lifeLostNetwork(eventHandler, ids);
    }

    void MobHit::handleOtherEntity(size_t otherEntity, GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        auto isBossOpt = componentsContainer.getComponent(otherEntity, GameEngine::ComponentsType::getComponentType("IsBoss"));
        if (isBossOpt.has_value())
            return;
        std::vector<size_t> ids = {bulletEntity};
        killMobNetwork(eventHandler, ids);
        componentsContainer.deleteEntity(otherEntity);
    }

    void MobHit::killMobNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill)
    {
         std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", entitiesToKill, "", std::vector<std::any>{});
         std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
         eventHandler.queueEvent("SEND_NETWORK", allMessage);
    }

    void MobHit::lifeLostNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill)
    {
         std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("LIFE_LOST", entitiesToKill, "", std::vector<std::any>{});
         std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
         eventHandler.queueEvent("SEND_NETWORK", allMessage);
    }

    void MobHit::flashMobNetwork(GameEngine::EventHandler &eventHandler, size_t mobEntity)
    {
        std::vector<size_t> ids = {mobEntity};
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("FLASH_ENTITY", ids, "", std::vector<std::any>{});
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

            auto hpComponentOpt = componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("Health"));
            auto lastHitComponentOpt = componentsContainer.getComponent(playerId, GameEngine::ComponentsType::getComponentType("CooldownHit"));
            if (hpComponentOpt.has_value() && lastHitComponentOpt.has_value()) {
                auto cooldownComponent = std::static_pointer_cast<CooldownHit>(lastHitComponentOpt.value());
                auto hpComponent = std::static_pointer_cast<Health>(hpComponentOpt.value());

                if (cooldownComponent->lastHit + std::chrono::milliseconds(90) > std::chrono::system_clock::now())
                    return;
                cooldownComponent->lastHit = std::chrono::system_clock::now();

                applyDamage(hpComponent, otherEntity, componentsContainer);

                if (hpComponent->currentHealth <= 0)
                    handleLifeLoss(playerId, componentsContainer, eventHandler);
            }
            handleOtherEntity(otherEntity, componentsContainer, eventHandler);
        } catch (std::exception &e) {
            std::cerr << "Error in PlayerHit::update: " << e.what() << std::endl;
        }
    }
}
