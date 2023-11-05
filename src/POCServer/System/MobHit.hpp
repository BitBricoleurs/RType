//
// Created by Bartosz on 10/9/23.
//

#pragma once

#include "ComponentsType.hpp"
#include "Damage.hpp"
#include "EventHandler.hpp"
#include "Health.hpp"
#include "ISystem.hpp"
#include "VelocityComponent.hpp"
#include "IsBullet.hpp"
#include "Message.hpp"
#include "UserMessage.hpp"
#include "PositionComponent2D.hpp"
#include "NetworkClientId.hpp"
#include "Score.hpp"

namespace Server {

    class MobHit : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;

      private:
        static void killMobNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill);
        static void applyDamage(const std::shared_ptr<Health>& hpComponent, size_t damageEntity, GameEngine::ComponentsContainer& componentsContainer);
        static void handleDeath(size_t deadEntity, GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler);
        static void handleBullet(size_t bulletEntity, GameEngine::ComponentsContainer& componentsContainer, GameEngine::EventHandler& eventHandler);
        static void flashMobNetwork(GameEngine::EventHandler &eventHandler, size_t mobEntity);
        static void updateScoreNetwork(GameEngine::EventHandler &eventHandler, size_t score);
};
}
