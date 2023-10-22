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
#include "NetworkClientId.hpp"

namespace Server {

    class MobHit : public GameEngine::ISystem {
    public:
        void update(GameEngine::ComponentsContainer &componentsContainer, GameEngine::EventHandler &eventHandler) override;

      private:
        void killMobNetwork(GameEngine::EventHandler &eventHandler, std::vector<size_t> &entitiesToKill);
    };
}
