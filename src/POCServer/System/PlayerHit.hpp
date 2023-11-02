//
// Created by Bartosz on 10/9/23.
//


#pragma once

#include "ISystem.hpp"
#include "EventHandler.hpp"
#include "ComponentsType.hpp"
#include "Health.hpp"
#include "Damage.hpp"
#include "UserMessage.hpp"
#include "Message.hpp"
#include "UserGameMode.hpp"
#include "CooldownHit.hpp"

namespace Server {

    class PlayerHit : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;

    private:
        void applyDamage(const std::shared_ptr<Health>& hpComponent, size_t damageEntity, GameEngine::ComponentsContainer &componentsContainer);
        void handleLifeLoss(size_t playerId, const std::shared_ptr<Health>& hpComponent, GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler);
        void handleOtherEntity(size_t otherEntity, GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler);
        void killMobNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill);
        void lifeLostNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &players, std::vector<std::any> &args);
        void flashNetwork(GameEngine::EventHandler &eventHandler, size_t entity);
        void sendDeathMessage(GameEngine::EventHandler &eventHandler, size_t entity);
    };
}