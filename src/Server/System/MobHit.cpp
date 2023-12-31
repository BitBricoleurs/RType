//
// Created by Bartosz on 10/9/23.
//

#include "MobHit.hpp"

namespace Server {

    void MobHit::applyDamage(const std::shared_ptr<Health>& hpComponent, size_t damageEntity, GameEngine::ComponentsContainer &componentsContainer) {
        auto damageComponentOpt = componentsContainer.getComponent(damageEntity, GameEngine::ComponentsType::getComponentType("Damage"));
        if (damageComponentOpt.has_value()) {
            auto damageComponent = std::static_pointer_cast<Damage>(damageComponentOpt.value());
            if (damageComponent)
                hpComponent->currentHealth -= damageComponent->damageValue;
        }
    }

    void MobHit::handleDeath(size_t deadEntity, GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        auto isPowerUp = componentsContainer.getComponent(deadEntity, GameEngine::ComponentsType::getComponentType("IsPowerUp"));
        auto posPowerUp = componentsContainer.getComponent(deadEntity, GameEngine::ComponentsType::getComponentType("PositionComponent2D"));
        if (isPowerUp.has_value() && posPowerUp.has_value()) {
            auto pos = std::static_pointer_cast<PhysicsEngine::PositionComponent2D>(posPowerUp.value())->pos;

            eventHandler.queueEvent("SpawnPowerUp", pos);
        }
        std::vector<size_t> ids = {deadEntity};
        killMobNetwork(eventHandler, ids);
        componentsContainer.deleteEntity(deadEntity);
    }

    void MobHit::handleBullet(size_t bulletEntity, GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        auto isBulletOpt = componentsContainer.getComponent(bulletEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
        if (isBulletOpt.has_value()) {
            auto isBullet = std::static_pointer_cast<IsBullet>(isBulletOpt.value());
            if (!isBullet->passingThrough) {
                std::vector<size_t> ids = {bulletEntity};
                killMobNetwork(eventHandler, ids);
                componentsContainer.deleteEntity(bulletEntity);
            }
        }
    }

    void MobHit::update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) {
        try {
            auto [firstEntity, secondEntity] = std::any_cast<std::pair<size_t, size_t>>(eventHandler.getTriggeredEvent().second);

            size_t mobEntity = 0, otherEntity = 0;
            if (componentsContainer.getComponent(firstEntity, GameEngine::ComponentsType::getComponentType("IsMob")).has_value()) {
                mobEntity = firstEntity;
                otherEntity = secondEntity;
            } else {
                mobEntity = secondEntity;
                otherEntity = firstEntity;
            }

            auto isBulletOpt = componentsContainer.getComponent(otherEntity, GameEngine::ComponentsType::getComponentType("IsBullet"));
            auto hpComponentOpt = componentsContainer.getComponent(mobEntity, GameEngine::ComponentsType::getComponentType("Health"));
            auto isLastMobOpt = componentsContainer.getComponent(mobEntity, GameEngine::ComponentsType::getComponentType("IsLastMob"));
            auto scoreEntity = componentsContainer.getEntityWithUniqueComponent(GameEngine::ComponentsType::getComponentType("Score"));
            auto scoreComponentOpt = componentsContainer.getComponent(scoreEntity, GameEngine::ComponentsType::getComponentType("Score"));
            if (hpComponentOpt.has_value() && isBulletOpt.has_value()) {
                auto isBullet = std::static_pointer_cast<IsBullet>(isBulletOpt.value());
                if (!isBullet->playerBullet)
                    return;
                auto hpComponent = std::static_pointer_cast<Health>(hpComponentOpt.value());

                applyDamage(hpComponent, otherEntity, componentsContainer);

                if (hpComponent->currentHealth <= 0) {
                    if (isLastMobOpt.has_value()) {
                            eventHandler.queueEvent("WIN_LEVEL");
                    }
                    if (scoreComponentOpt.has_value()) {
                        auto scoreComponent = std::static_pointer_cast<Score>(scoreComponentOpt.value());
                        scoreComponent->score += hpComponent->maxHealth;
                        updateScoreNetwork(eventHandler, scoreComponent->score);
                    }
                    handleDeath(mobEntity, componentsContainer, eventHandler);
                }
                else
                    flashMobNetwork(eventHandler, mobEntity);
            }

            handleBullet(otherEntity, componentsContainer, eventHandler);

        } catch (std::exception &e) {
            std::cerr << "Error in MobHit::update: " << e.what() << std::endl;
        }
    }


    void MobHit::killMobNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill)
    {
         std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("DELETED_ENTITY", entitiesToKill, "", std::vector<std::any>{});
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

    void MobHit::updateScoreNetwork(GameEngine::EventHandler &eventHandler, size_t score)
    {
        std::vector<size_t> ids = {};
        int scoreInt = score;
        std::shared_ptr<Network::Message> message = std::make_shared<Network::Message>("UPDATE_SCORE", ids, "INT", std::vector<std::any>{scoreInt});
        std::shared_ptr<Network::AllUsersMessage> allMessage = std::make_shared<Network::AllUsersMessage>(message);
        eventHandler.queueEvent("SEND_NETWORK", allMessage);
    }

}